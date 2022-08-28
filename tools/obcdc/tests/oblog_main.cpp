/**
 * Copyright (c) 2021 OceanBase
 * OceanBase CE is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#define USING_LOG_PREFIX OBLOG_TAILF

#include "oblog_main.h"
#include "ob_log_instance.h"    // ObLogInstance

#include <stdio.h>        // fprintf
#include <getopt.h>       // getopt_long
#include <stdlib.h>       // strtoull

#define LOG_STD(str, ...) \
  do { \
    fprintf(stderr, str, ##__VA_ARGS__); \
  } while (0)

using namespace oceanbase::common;
namespace oceanbase
{
namespace liboblog
{

ObLogMain &ObLogMain::get_instance()
{
  static ObLogMain oblog_main;
  return oblog_main;
}

ObLogMain::ObLogMain() : inited_(false),
                         oblog_(NULL),
                         oblog_factory_(),
                         br_printer_(),
                         only_print_hex_(false),
                         print_hex_(false),
                         print_lob_md5_(false),
                         use_daemon_(false),
                         data_file_(NULL),
                         heartbeat_file_(NULL),
                         run_time_us_(-1),
                         config_file_(NULL),
                         print_console_(false),
                         verify_mode_(false),
                         enable_reentrant_(false),
                         output_br_detail_(false),
                         start_timestamp_usec_(0),
                         tenant_id_(OB_INVALID_TENANT_ID),
                         tg_match_pattern_(NULL),
                         last_heartbeat_timestamp_micro_sec_(0),
                         stop_flag_(true)
{
}

ObLogMain::~ObLogMain()
{
  destroy();
}

int ObLogMain::init(int argc, char **argv)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(parse_args_(argc, argv))) {
    if (OB_IN_STOP_STATE != ret) {
      LOG_ERROR("parse arguments fail", K(ret), K(argc));
    }
  } else if (! check_args_()) {
    LOG_ERROR("check arguments fail");
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_FAIL(br_printer_.init(data_file_, heartbeat_file_, print_console_, only_print_hex_, print_hex_,
      print_lob_md5_, verify_mode_, output_br_detail_))) {
    LOG_ERROR("init binlog record printer fail", K(ret), K(data_file_), K(heartbeat_file_),
        K(print_console_), K(only_print_hex_), K(print_hex_), K(print_lob_md5_), K(verify_mode_), K_(output_br_detail));
  } else {
    stop_flag_ = true;
    inited_ = true;
    last_heartbeat_timestamp_micro_sec_ = start_timestamp_usec_;
  }

  return ret;
}

void ObLogMain::destroy()
{
  stop();

  inited_ = false;
  oblog_ = NULL;
  only_print_hex_ = false;
  print_hex_ = false;
  print_lob_md5_ = false;
  use_daemon_ = false;
  data_file_ = NULL;
  heartbeat_file_ = NULL;
  run_time_us_ = 0;
  config_file_ = NULL;
  print_console_ = false;
  verify_mode_ = false;
  enable_reentrant_ = false;
  start_timestamp_usec_ = 0;
  tenant_id_ = OB_INVALID_TENANT_ID;
  tg_match_pattern_ = NULL;
  last_heartbeat_timestamp_micro_sec_ = 0;
  stop_flag_ = true;
  output_br_detail_ = false;
  br_printer_.destroy();
}

int ObLogMain::parse_args_(int argc, char **argv)
{
  int ret = OB_SUCCESS;

  // option variables
  int opt = -1;
  const char *opt_string = "ivdD:f:hH:oVt:rR:OxmT:P";
  struct option long_opts[] =
  {
    {"use_daemon", 0, NULL, 'd'},
    {"data_file", 1, NULL, 'D'},
    {"config_file",1,NULL,'f'},
    {"help", 0, NULL, 'h'},
    {"heartbeat_file", 1, NULL, 'H'},
    {"print_console",0,NULL, 'o'},
    {"verify_mode", 0, NULL, 'V'},
    {"start_timestamp", 1, NULL, 't'},                // t: Represents a start-up timestamp in seconds
    {"start_timestamp_usec", 1, NULL, 'T'},           // T: Represents a start-up timestamp in microsecond units
    {"data_start_schema_version", 1, NULL, 's'},
    {"enable_reentrant", 0, NULL, 'r'},
    {"run_time_sec", 1, NULL, 'R'},
    {"only_print_hex", 0, NULL, 'O'},
    {"print_hex", 0, NULL, 'x'},
    {"print_lob_md5", 0, NULL, 'm'},
    {"version", 0, NULL, 'v'},
    {"verify_begin_trans_id", 0, NULL, 'P'},
    {"output_br_detail", 0, NULL, 'i'},
    {0, 0, 0, 0}
  };

  if (argc <= 1) {
    print_usage(argv[0]);
    ret = OB_IN_STOP_STATE;
  }

  // Parse command line
  while (OB_SUCCESS == ret && (opt = getopt_long(argc, argv, opt_string, long_opts, NULL)) != -1) {
    switch (opt) {
      case 'f': {
        config_file_ = optarg;
        break;
      }

      case 'd': {
        use_daemon_ = true;
        break;
      }

      case 'D': {
        data_file_ = optarg;
        break;
      }

      case 'h': {
        print_usage(argv[0]);
        ret = OB_IN_STOP_STATE;
        break;
      }

      case 'H': {
        heartbeat_file_ = optarg;
        break;
      }

      case 'o': {
        print_console_ = true;
        break;
      }

      case 'V': {
        verify_mode_ = true;
        break;
      }

      case 't': {
        start_timestamp_usec_ = strtoll(optarg, NULL, 10) * 1000000L;
        break;
      }

      case 'T': {
        start_timestamp_usec_ = strtoll(optarg, NULL, 10);
        break;
      }

      case 'r': {
        enable_reentrant_ = true;
        break;
      }

      case 'R': {
        run_time_us_ = strtoll(optarg, NULL, 10) * 1000000;
        LOG_STD("RUN_TIME: %ld seconds\n", run_time_us_ / 1000000);
        break;
      }

      case 'O': {
        only_print_hex_ = true;
        break;
      }

      case 'x': {
        print_hex_ = true;
        break;
      }

      case 'm': {
        print_lob_md5_ = true;
        break;
      }

      case 'i': {
        // output detail info of binlog record, default off
        output_br_detail_ = true;
        break;
      }

      case 'v': {
        ObLogInstance::print_version();
        ret = OB_IN_STOP_STATE;
        break;
      }
      case 'P': {
        // Verify that the begin trans_id function does not fall back and is turned on by default
        LOG_STD("verify_begin_trans_id\n");
        break;
      }

      default:
        ret = OB_ERROR;
        LOG_ERROR("unknown parameters", K(opt), K(opt_string));
        break;
    } // end switch
  } // end while

  return ret;
}

void ObLogMain::print_usage(const char *prog_name)
{
  LOG_STD("USAGE: %s -f config_file_path\n\n"
      "   -v, --version                       print version\n"
      "   -d, --use_daemon                    start as daemon, default no daemon\n"
      "   -D, --data_file                     data file used to store data\n"
      "   -f, --config_file                   configuration file\n"
      "   -h, --help                          display this help\n"
      "   -H, --heartbeat_file                heartbeat file used to store heartbeat data\n"
      "   -o, --print_console                 output result to stderr or stdout, default not output\n"
      "   -V, --verify_mode                   start verify mode\n"
      "   -t, --start_timestamp               start timestamp in second, default current timestamp\n"
      "   -T, --start_timestamp_usec          start timestamp in micro second, default current timestamp\n"
      "   -r, --enable_reentrant              enable reentrant after stop, default disable\n"
      "   -R, --run_time_sec                  run time in seconds, default -1, means to run forever\n"
      "   -x, --print_hex                     print hex for newcolumn, to check implicit char\n"
      "   -m, --print_lob_md5                 print md5 info for LOB data\n"
      "   -i, --output_br_detail              output immutable detail info of binlog record, default not output\n"

      "\neg: %s -f liboblog.conf\n",
      prog_name, prog_name);
}

bool ObLogMain::check_args_()
{
  int ret = OB_SUCCESS;
  int nochdir = 1;
  int noclose = 0;

  if (NULL == config_file_) {
    LOG_ERROR("config file is missing");
    ret = OB_INVALID_ARGUMENT;
  } else if (use_daemon_ && daemon(nochdir, noclose) < 0) {
    LOG_ERROR("create daemon process error", K(errno), KERRMSG);
    ret = OB_ERR_UNEXPECTED;
  }

  return OB_SUCCESS == ret;
}

int ObLogMain::start()
{
  int ret = OB_SUCCESS;
  if (! inited_) {
    ret = OB_NOT_INIT;
  } else if (NULL != oblog_) {
    LOG_ERROR("oblog has started");
    ret = OB_NOT_SUPPORTED;
  } else if (stop_flag_) {
    stop_flag_ = false;

    if (NULL == (oblog_ = oblog_factory_.construct_oblog())) {
      LOG_ERROR("construct oblog fail");
      ret = OB_INIT_FAIL;
    } else {
      ObLogInstance *instance = (ObLogInstance *)oblog_;
      // Disable redirected output
      instance->set_disable_redirect_log(true);

      if (OB_FAIL(instance->init_with_start_tstamp_usec(config_file_, start_timestamp_usec_, handle_error))) {
        LOG_ERROR("init oblog fail", K(ret), K_(config_file), K_(start_timestamp_usec), KP(handle_error));
      } else {
        // do nothing
      }

      if (OB_SUCC(ret)) {
        if (OB_FAIL(oblog_->launch())) {
          LOG_ERROR("launch oblog fail", K(ret));
        } else {
          OB_LOGGER.set_log_level(instance->get_log_level());
          OB_LOGGER.set_file_name(instance->get_log_file(), true, false);
          LOG_INFO("start oblog success");
        }
      }
    }
  }

  return ret;
}

void ObLogMain::stop()
{
  stop_flag_ = true;

  if (NULL != oblog_) {
    oblog_->stop();
    oblog_->destroy();
    oblog_factory_.deconstruct(oblog_);
    oblog_ = NULL;
  }
}

void ObLogMain::run()
{
  if (inited_ && NULL != oblog_) {
    int ret = OB_SUCCESS;
    int64_t end_time = ::oceanbase::common::ObTimeUtility::current_time() + run_time_us_;

    while (OB_SUCCESS == ret && ! stop_flag_) {
      ILogRecord *br = NULL;
      ret = oblog_->next_record(&br, NEXT_RECORD_TIMEOUT);

      if (OB_SUCC(ret)) {
        if (OB_FAIL(verify_record_info_(br))) {
          LOG_ERROR("verify_record_info_ fail", K(ret), K(br));
        }
        // output binlog record
        else if (OB_FAIL(br_printer_.print_binlog_record(br))) {
          LOG_ERROR("print_binlog_record fail", K(ret));
        } else {
          oblog_->release_record(br);
          br = NULL;
        }
      } else if (OB_TIMEOUT == ret) {
        int64_t left_time = end_time - ::oceanbase::common::ObTimeUtility::current_time();
        if (run_time_us_ > 0 && left_time <= 0) {
          ret = OB_TIMEOUT;
        } else {
          ret = OB_SUCCESS;
        }
      } else if (OB_ITER_END == ret) {
        LOG_INFO("iterate BinlogRecord to the END");
        stop_flag_ = true;
        ret = OB_SUCCESS;
      } else if (OB_IN_STOP_STATE == ret) {
        stop_flag_ = true;
        ret = OB_SUCCESS;
      } else {
        LOG_ERROR("next_record fail", K(ret));
      }
    }
  }
}

void ObLogMain::handle_error(const ObLogError &err)
{
  LOG_INFO("stop oblog on error", "level", err.level_, "errno", err.errno_, "errmsg", err.errmsg_);
  ObLogMain::get_instance().mark_stop_flag(true);
}

int ObLogMain::verify_record_info_(ILogRecord *br)
{
  int ret = OB_SUCCESS;
  static bool is_first_br = true;
  ObLogBR *oblog_br = NULL;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("ObLogMain has not inited");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(br)) {
    LOG_ERROR("br is null");
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_ISNULL(oblog_br = reinterpret_cast<ObLogBR *>(br->getUserData()))) {
    LOG_ERROR("get user data fail", K(br), K(oblog_br));
    ret = OB_INVALID_ARGUMENT;
  } else {
    // heartbeat, updtae last_heartbeat_timestamp_micro_sec_
    if (HEARTBEAT == br->recordType()) {
      int64_t timestamp_usec = OB_INVALID_TIMESTAMP;
      if (is_first_br) {
        // oblog_tailf -f $CONFIG -t 0 means start at current time
        // The liboblog start timestamp is not available
        // So the first BinlogRecord is obtained based on the checkpoint
        timestamp_usec = br->getCheckpoint1() * 1000000 + br->getCheckpoint2();
        is_first_br = false;
      } else {
        timestamp_usec = br->getTimestamp() * 1000000 + br->getRecordUsec();
      }
      last_heartbeat_timestamp_micro_sec_ = std::max(timestamp_usec, last_heartbeat_timestamp_micro_sec_);
    }

    // Calibration timestamp and checkpoint
    int64_t precise_timestamp = oblog_br->get_precise_timestamp();
    int64_t timestamp_sec = precise_timestamp / 1000000;
    int64_t timestamp_usec = precise_timestamp % 1000000;
    int64_t expect_checkpoint1 = last_heartbeat_timestamp_micro_sec_ / 1000000;
    int64_t expect_checkpoint2 = last_heartbeat_timestamp_micro_sec_ % 1000000;

    if (OB_UNLIKELY(timestamp_sec != br->getTimestamp())
        || OB_UNLIKELY(timestamp_usec != br->getRecordUsec())) {
      LOG_ERROR("timestamp is not right", K(precise_timestamp), "br_sec", br->getTimestamp(),
          "br_usec", br->getRecordUsec());
      ret = OB_ERR_UNEXPECTED;
    } else if (OB_UNLIKELY(expect_checkpoint1 != br->getCheckpoint1())
        || OB_UNLIKELY(expect_checkpoint2 != br->getCheckpoint2())) {
      LOG_ERROR("checkpoint is not right", K(br), K(last_heartbeat_timestamp_micro_sec_),
          K(expect_checkpoint1), "br_checkpoint1", br->getCheckpoint1(),
          K(expect_checkpoint2), "br_checkpoint2", br->getCheckpoint2(),
          "getTimestamp", br->getTimestamp(), "getRecordUsec", br->getRecordUsec(),
          K(is_first_br));
      ret = OB_ERR_UNEXPECTED;
    } else {
      // succ
    }
  }

  return ret;
}

} // namespace liboblog
} // namespace oceanbase
