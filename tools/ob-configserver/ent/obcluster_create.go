// Code generated by entc, DO NOT EDIT.

package ent

import (
	"context"
	"errors"
	"fmt"
	"time"

	"entgo.io/ent/dialect/sql"
	"entgo.io/ent/dialect/sql/sqlgraph"
	"entgo.io/ent/schema/field"
	"github.com/oceanbase/configserver/ent/obcluster"
)

// ObClusterCreate is the builder for creating a ObCluster entity.
type ObClusterCreate struct {
	config
	mutation *ObClusterMutation
	hooks    []Hook
	conflict []sql.ConflictOption
}

// SetCreateTime sets the "create_time" field.
func (occ *ObClusterCreate) SetCreateTime(t time.Time) *ObClusterCreate {
	occ.mutation.SetCreateTime(t)
	return occ
}

// SetNillableCreateTime sets the "create_time" field if the given value is not nil.
func (occ *ObClusterCreate) SetNillableCreateTime(t *time.Time) *ObClusterCreate {
	if t != nil {
		occ.SetCreateTime(*t)
	}
	return occ
}

// SetUpdateTime sets the "update_time" field.
func (occ *ObClusterCreate) SetUpdateTime(t time.Time) *ObClusterCreate {
	occ.mutation.SetUpdateTime(t)
	return occ
}

// SetNillableUpdateTime sets the "update_time" field if the given value is not nil.
func (occ *ObClusterCreate) SetNillableUpdateTime(t *time.Time) *ObClusterCreate {
	if t != nil {
		occ.SetUpdateTime(*t)
	}
	return occ
}

// SetName sets the "name" field.
func (occ *ObClusterCreate) SetName(s string) *ObClusterCreate {
	occ.mutation.SetName(s)
	return occ
}

// SetObClusterID sets the "ob_cluster_id" field.
func (occ *ObClusterCreate) SetObClusterID(i int64) *ObClusterCreate {
	occ.mutation.SetObClusterID(i)
	return occ
}

// SetType sets the "type" field.
func (occ *ObClusterCreate) SetType(s string) *ObClusterCreate {
	occ.mutation.SetType(s)
	return occ
}

// SetRootserviceJSON sets the "rootservice_json" field.
func (occ *ObClusterCreate) SetRootserviceJSON(s string) *ObClusterCreate {
	occ.mutation.SetRootserviceJSON(s)
	return occ
}

// Mutation returns the ObClusterMutation object of the builder.
func (occ *ObClusterCreate) Mutation() *ObClusterMutation {
	return occ.mutation
}

// Save creates the ObCluster in the database.
func (occ *ObClusterCreate) Save(ctx context.Context) (*ObCluster, error) {
	var (
		err  error
		node *ObCluster
	)
	occ.defaults()
	if len(occ.hooks) == 0 {
		if err = occ.check(); err != nil {
			return nil, err
		}
		node, err = occ.sqlSave(ctx)
	} else {
		var mut Mutator = MutateFunc(func(ctx context.Context, m Mutation) (Value, error) {
			mutation, ok := m.(*ObClusterMutation)
			if !ok {
				return nil, fmt.Errorf("unexpected mutation type %T", m)
			}
			if err = occ.check(); err != nil {
				return nil, err
			}
			occ.mutation = mutation
			if node, err = occ.sqlSave(ctx); err != nil {
				return nil, err
			}
			mutation.id = &node.ID
			mutation.done = true
			return node, err
		})
		for i := len(occ.hooks) - 1; i >= 0; i-- {
			if occ.hooks[i] == nil {
				return nil, fmt.Errorf("ent: uninitialized hook (forgotten import ent/runtime?)")
			}
			mut = occ.hooks[i](mut)
		}
		if _, err := mut.Mutate(ctx, occ.mutation); err != nil {
			return nil, err
		}
	}
	return node, err
}

// SaveX calls Save and panics if Save returns an error.
func (occ *ObClusterCreate) SaveX(ctx context.Context) *ObCluster {
	v, err := occ.Save(ctx)
	if err != nil {
		panic(err)
	}
	return v
}

// Exec executes the query.
func (occ *ObClusterCreate) Exec(ctx context.Context) error {
	_, err := occ.Save(ctx)
	return err
}

// ExecX is like Exec, but panics if an error occurs.
func (occ *ObClusterCreate) ExecX(ctx context.Context) {
	if err := occ.Exec(ctx); err != nil {
		panic(err)
	}
}

// defaults sets the default values of the builder before save.
func (occ *ObClusterCreate) defaults() {
	if _, ok := occ.mutation.CreateTime(); !ok {
		v := obcluster.DefaultCreateTime()
		occ.mutation.SetCreateTime(v)
	}
	if _, ok := occ.mutation.UpdateTime(); !ok {
		v := obcluster.DefaultUpdateTime()
		occ.mutation.SetUpdateTime(v)
	}
}

// check runs all checks and user-defined validators on the builder.
func (occ *ObClusterCreate) check() error {
	if _, ok := occ.mutation.CreateTime(); !ok {
		return &ValidationError{Name: "create_time", err: errors.New(`ent: missing required field "ObCluster.create_time"`)}
	}
	if _, ok := occ.mutation.UpdateTime(); !ok {
		return &ValidationError{Name: "update_time", err: errors.New(`ent: missing required field "ObCluster.update_time"`)}
	}
	if _, ok := occ.mutation.Name(); !ok {
		return &ValidationError{Name: "name", err: errors.New(`ent: missing required field "ObCluster.name"`)}
	}
	if _, ok := occ.mutation.ObClusterID(); !ok {
		return &ValidationError{Name: "ob_cluster_id", err: errors.New(`ent: missing required field "ObCluster.ob_cluster_id"`)}
	}
	if v, ok := occ.mutation.ObClusterID(); ok {
		if err := obcluster.ObClusterIDValidator(v); err != nil {
			return &ValidationError{Name: "ob_cluster_id", err: fmt.Errorf(`ent: validator failed for field "ObCluster.ob_cluster_id": %w`, err)}
		}
	}
	if _, ok := occ.mutation.GetType(); !ok {
		return &ValidationError{Name: "type", err: errors.New(`ent: missing required field "ObCluster.type"`)}
	}
	if _, ok := occ.mutation.RootserviceJSON(); !ok {
		return &ValidationError{Name: "rootservice_json", err: errors.New(`ent: missing required field "ObCluster.rootservice_json"`)}
	}
	return nil
}

func (occ *ObClusterCreate) sqlSave(ctx context.Context) (*ObCluster, error) {
	_node, _spec := occ.createSpec()
	if err := sqlgraph.CreateNode(ctx, occ.driver, _spec); err != nil {
		if sqlgraph.IsConstraintError(err) {
			err = &ConstraintError{err.Error(), err}
		}
		return nil, err
	}
	id := _spec.ID.Value.(int64)
	_node.ID = int(id)
	return _node, nil
}

func (occ *ObClusterCreate) createSpec() (*ObCluster, *sqlgraph.CreateSpec) {
	var (
		_node = &ObCluster{config: occ.config}
		_spec = &sqlgraph.CreateSpec{
			Table: obcluster.Table,
			ID: &sqlgraph.FieldSpec{
				Type:   field.TypeInt,
				Column: obcluster.FieldID,
			},
		}
	)
	_spec.OnConflict = occ.conflict
	if value, ok := occ.mutation.CreateTime(); ok {
		_spec.Fields = append(_spec.Fields, &sqlgraph.FieldSpec{
			Type:   field.TypeTime,
			Value:  value,
			Column: obcluster.FieldCreateTime,
		})
		_node.CreateTime = value
	}
	if value, ok := occ.mutation.UpdateTime(); ok {
		_spec.Fields = append(_spec.Fields, &sqlgraph.FieldSpec{
			Type:   field.TypeTime,
			Value:  value,
			Column: obcluster.FieldUpdateTime,
		})
		_node.UpdateTime = value
	}
	if value, ok := occ.mutation.Name(); ok {
		_spec.Fields = append(_spec.Fields, &sqlgraph.FieldSpec{
			Type:   field.TypeString,
			Value:  value,
			Column: obcluster.FieldName,
		})
		_node.Name = value
	}
	if value, ok := occ.mutation.ObClusterID(); ok {
		_spec.Fields = append(_spec.Fields, &sqlgraph.FieldSpec{
			Type:   field.TypeInt64,
			Value:  value,
			Column: obcluster.FieldObClusterID,
		})
		_node.ObClusterID = value
	}
	if value, ok := occ.mutation.GetType(); ok {
		_spec.Fields = append(_spec.Fields, &sqlgraph.FieldSpec{
			Type:   field.TypeString,
			Value:  value,
			Column: obcluster.FieldType,
		})
		_node.Type = value
	}
	if value, ok := occ.mutation.RootserviceJSON(); ok {
		_spec.Fields = append(_spec.Fields, &sqlgraph.FieldSpec{
			Type:   field.TypeString,
			Value:  value,
			Column: obcluster.FieldRootserviceJSON,
		})
		_node.RootserviceJSON = value
	}
	return _node, _spec
}

// OnConflict allows configuring the `ON CONFLICT` / `ON DUPLICATE KEY` clause
// of the `INSERT` statement. For example:
//
//	client.ObCluster.Create().
//		SetCreateTime(v).
//		OnConflict(
//			// Update the row with the new values
//			// the was proposed for insertion.
//			sql.ResolveWithNewValues(),
//		).
//		// Override some of the fields with custom
//		// update values.
//		Update(func(u *ent.ObClusterUpsert) {
//			SetCreateTime(v+v).
//		}).
//		Exec(ctx)
//
func (occ *ObClusterCreate) OnConflict(opts ...sql.ConflictOption) *ObClusterUpsertOne {
	occ.conflict = opts
	return &ObClusterUpsertOne{
		create: occ,
	}
}

// OnConflictColumns calls `OnConflict` and configures the columns
// as conflict target. Using this option is equivalent to using:
//
//	client.ObCluster.Create().
//		OnConflict(sql.ConflictColumns(columns...)).
//		Exec(ctx)
//
func (occ *ObClusterCreate) OnConflictColumns(columns ...string) *ObClusterUpsertOne {
	occ.conflict = append(occ.conflict, sql.ConflictColumns(columns...))
	return &ObClusterUpsertOne{
		create: occ,
	}
}

type (
	// ObClusterUpsertOne is the builder for "upsert"-ing
	//  one ObCluster node.
	ObClusterUpsertOne struct {
		create *ObClusterCreate
	}

	// ObClusterUpsert is the "OnConflict" setter.
	ObClusterUpsert struct {
		*sql.UpdateSet
	}
)

// SetCreateTime sets the "create_time" field.
func (u *ObClusterUpsert) SetCreateTime(v time.Time) *ObClusterUpsert {
	u.Set(obcluster.FieldCreateTime, v)
	return u
}

// UpdateCreateTime sets the "create_time" field to the value that was provided on create.
func (u *ObClusterUpsert) UpdateCreateTime() *ObClusterUpsert {
	u.SetExcluded(obcluster.FieldCreateTime)
	return u
}

// SetUpdateTime sets the "update_time" field.
func (u *ObClusterUpsert) SetUpdateTime(v time.Time) *ObClusterUpsert {
	u.Set(obcluster.FieldUpdateTime, v)
	return u
}

// UpdateUpdateTime sets the "update_time" field to the value that was provided on create.
func (u *ObClusterUpsert) UpdateUpdateTime() *ObClusterUpsert {
	u.SetExcluded(obcluster.FieldUpdateTime)
	return u
}

// SetName sets the "name" field.
func (u *ObClusterUpsert) SetName(v string) *ObClusterUpsert {
	u.Set(obcluster.FieldName, v)
	return u
}

// UpdateName sets the "name" field to the value that was provided on create.
func (u *ObClusterUpsert) UpdateName() *ObClusterUpsert {
	u.SetExcluded(obcluster.FieldName)
	return u
}

// SetObClusterID sets the "ob_cluster_id" field.
func (u *ObClusterUpsert) SetObClusterID(v int64) *ObClusterUpsert {
	u.Set(obcluster.FieldObClusterID, v)
	return u
}

// UpdateObClusterID sets the "ob_cluster_id" field to the value that was provided on create.
func (u *ObClusterUpsert) UpdateObClusterID() *ObClusterUpsert {
	u.SetExcluded(obcluster.FieldObClusterID)
	return u
}

// AddObClusterID adds v to the "ob_cluster_id" field.
func (u *ObClusterUpsert) AddObClusterID(v int64) *ObClusterUpsert {
	u.Add(obcluster.FieldObClusterID, v)
	return u
}

// SetType sets the "type" field.
func (u *ObClusterUpsert) SetType(v string) *ObClusterUpsert {
	u.Set(obcluster.FieldType, v)
	return u
}

// UpdateType sets the "type" field to the value that was provided on create.
func (u *ObClusterUpsert) UpdateType() *ObClusterUpsert {
	u.SetExcluded(obcluster.FieldType)
	return u
}

// SetRootserviceJSON sets the "rootservice_json" field.
func (u *ObClusterUpsert) SetRootserviceJSON(v string) *ObClusterUpsert {
	u.Set(obcluster.FieldRootserviceJSON, v)
	return u
}

// UpdateRootserviceJSON sets the "rootservice_json" field to the value that was provided on create.
func (u *ObClusterUpsert) UpdateRootserviceJSON() *ObClusterUpsert {
	u.SetExcluded(obcluster.FieldRootserviceJSON)
	return u
}

// UpdateNewValues updates the mutable fields using the new values that were set on create.
// Using this option is equivalent to using:
//
//	client.ObCluster.Create().
//		OnConflict(
//			sql.ResolveWithNewValues(),
//		).
//		Exec(ctx)
//
func (u *ObClusterUpsertOne) UpdateNewValues() *ObClusterUpsertOne {
	u.create.conflict = append(u.create.conflict, sql.ResolveWithNewValues())
	return u
}

// Ignore sets each column to itself in case of conflict.
// Using this option is equivalent to using:
//
//  client.ObCluster.Create().
//      OnConflict(sql.ResolveWithIgnore()).
//      Exec(ctx)
//
func (u *ObClusterUpsertOne) Ignore() *ObClusterUpsertOne {
	u.create.conflict = append(u.create.conflict, sql.ResolveWithIgnore())
	return u
}

// DoNothing configures the conflict_action to `DO NOTHING`.
// Supported only by SQLite and PostgreSQL.
func (u *ObClusterUpsertOne) DoNothing() *ObClusterUpsertOne {
	u.create.conflict = append(u.create.conflict, sql.DoNothing())
	return u
}

// Update allows overriding fields `UPDATE` values. See the ObClusterCreate.OnConflict
// documentation for more info.
func (u *ObClusterUpsertOne) Update(set func(*ObClusterUpsert)) *ObClusterUpsertOne {
	u.create.conflict = append(u.create.conflict, sql.ResolveWith(func(update *sql.UpdateSet) {
		set(&ObClusterUpsert{UpdateSet: update})
	}))
	return u
}

// SetCreateTime sets the "create_time" field.
func (u *ObClusterUpsertOne) SetCreateTime(v time.Time) *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.SetCreateTime(v)
	})
}

// UpdateCreateTime sets the "create_time" field to the value that was provided on create.
func (u *ObClusterUpsertOne) UpdateCreateTime() *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.UpdateCreateTime()
	})
}

// SetUpdateTime sets the "update_time" field.
func (u *ObClusterUpsertOne) SetUpdateTime(v time.Time) *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.SetUpdateTime(v)
	})
}

// UpdateUpdateTime sets the "update_time" field to the value that was provided on create.
func (u *ObClusterUpsertOne) UpdateUpdateTime() *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.UpdateUpdateTime()
	})
}

// SetName sets the "name" field.
func (u *ObClusterUpsertOne) SetName(v string) *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.SetName(v)
	})
}

// UpdateName sets the "name" field to the value that was provided on create.
func (u *ObClusterUpsertOne) UpdateName() *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.UpdateName()
	})
}

// SetObClusterID sets the "ob_cluster_id" field.
func (u *ObClusterUpsertOne) SetObClusterID(v int64) *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.SetObClusterID(v)
	})
}

// AddObClusterID adds v to the "ob_cluster_id" field.
func (u *ObClusterUpsertOne) AddObClusterID(v int64) *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.AddObClusterID(v)
	})
}

// UpdateObClusterID sets the "ob_cluster_id" field to the value that was provided on create.
func (u *ObClusterUpsertOne) UpdateObClusterID() *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.UpdateObClusterID()
	})
}

// SetType sets the "type" field.
func (u *ObClusterUpsertOne) SetType(v string) *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.SetType(v)
	})
}

// UpdateType sets the "type" field to the value that was provided on create.
func (u *ObClusterUpsertOne) UpdateType() *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.UpdateType()
	})
}

// SetRootserviceJSON sets the "rootservice_json" field.
func (u *ObClusterUpsertOne) SetRootserviceJSON(v string) *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.SetRootserviceJSON(v)
	})
}

// UpdateRootserviceJSON sets the "rootservice_json" field to the value that was provided on create.
func (u *ObClusterUpsertOne) UpdateRootserviceJSON() *ObClusterUpsertOne {
	return u.Update(func(s *ObClusterUpsert) {
		s.UpdateRootserviceJSON()
	})
}

// Exec executes the query.
func (u *ObClusterUpsertOne) Exec(ctx context.Context) error {
	if len(u.create.conflict) == 0 {
		return errors.New("ent: missing options for ObClusterCreate.OnConflict")
	}
	return u.create.Exec(ctx)
}

// ExecX is like Exec, but panics if an error occurs.
func (u *ObClusterUpsertOne) ExecX(ctx context.Context) {
	if err := u.create.Exec(ctx); err != nil {
		panic(err)
	}
}

// Exec executes the UPSERT query and returns the inserted/updated ID.
func (u *ObClusterUpsertOne) ID(ctx context.Context) (id int, err error) {
	node, err := u.create.Save(ctx)
	if err != nil {
		return id, err
	}
	return node.ID, nil
}

// IDX is like ID, but panics if an error occurs.
func (u *ObClusterUpsertOne) IDX(ctx context.Context) int {
	id, err := u.ID(ctx)
	if err != nil {
		panic(err)
	}
	return id
}

// ObClusterCreateBulk is the builder for creating many ObCluster entities in bulk.
type ObClusterCreateBulk struct {
	config
	builders []*ObClusterCreate
	conflict []sql.ConflictOption
}

// Save creates the ObCluster entities in the database.
func (occb *ObClusterCreateBulk) Save(ctx context.Context) ([]*ObCluster, error) {
	specs := make([]*sqlgraph.CreateSpec, len(occb.builders))
	nodes := make([]*ObCluster, len(occb.builders))
	mutators := make([]Mutator, len(occb.builders))
	for i := range occb.builders {
		func(i int, root context.Context) {
			builder := occb.builders[i]
			builder.defaults()
			var mut Mutator = MutateFunc(func(ctx context.Context, m Mutation) (Value, error) {
				mutation, ok := m.(*ObClusterMutation)
				if !ok {
					return nil, fmt.Errorf("unexpected mutation type %T", m)
				}
				if err := builder.check(); err != nil {
					return nil, err
				}
				builder.mutation = mutation
				nodes[i], specs[i] = builder.createSpec()
				var err error
				if i < len(mutators)-1 {
					_, err = mutators[i+1].Mutate(root, occb.builders[i+1].mutation)
				} else {
					spec := &sqlgraph.BatchCreateSpec{Nodes: specs}
					spec.OnConflict = occb.conflict
					// Invoke the actual operation on the latest mutation in the chain.
					if err = sqlgraph.BatchCreate(ctx, occb.driver, spec); err != nil {
						if sqlgraph.IsConstraintError(err) {
							err = &ConstraintError{err.Error(), err}
						}
					}
				}
				if err != nil {
					return nil, err
				}
				mutation.id = &nodes[i].ID
				mutation.done = true
				if specs[i].ID.Value != nil {
					id := specs[i].ID.Value.(int64)
					nodes[i].ID = int(id)
				}
				return nodes[i], nil
			})
			for i := len(builder.hooks) - 1; i >= 0; i-- {
				mut = builder.hooks[i](mut)
			}
			mutators[i] = mut
		}(i, ctx)
	}
	if len(mutators) > 0 {
		if _, err := mutators[0].Mutate(ctx, occb.builders[0].mutation); err != nil {
			return nil, err
		}
	}
	return nodes, nil
}

// SaveX is like Save, but panics if an error occurs.
func (occb *ObClusterCreateBulk) SaveX(ctx context.Context) []*ObCluster {
	v, err := occb.Save(ctx)
	if err != nil {
		panic(err)
	}
	return v
}

// Exec executes the query.
func (occb *ObClusterCreateBulk) Exec(ctx context.Context) error {
	_, err := occb.Save(ctx)
	return err
}

// ExecX is like Exec, but panics if an error occurs.
func (occb *ObClusterCreateBulk) ExecX(ctx context.Context) {
	if err := occb.Exec(ctx); err != nil {
		panic(err)
	}
}

// OnConflict allows configuring the `ON CONFLICT` / `ON DUPLICATE KEY` clause
// of the `INSERT` statement. For example:
//
//	client.ObCluster.CreateBulk(builders...).
//		OnConflict(
//			// Update the row with the new values
//			// the was proposed for insertion.
//			sql.ResolveWithNewValues(),
//		).
//		// Override some of the fields with custom
//		// update values.
//		Update(func(u *ent.ObClusterUpsert) {
//			SetCreateTime(v+v).
//		}).
//		Exec(ctx)
//
func (occb *ObClusterCreateBulk) OnConflict(opts ...sql.ConflictOption) *ObClusterUpsertBulk {
	occb.conflict = opts
	return &ObClusterUpsertBulk{
		create: occb,
	}
}

// OnConflictColumns calls `OnConflict` and configures the columns
// as conflict target. Using this option is equivalent to using:
//
//	client.ObCluster.Create().
//		OnConflict(sql.ConflictColumns(columns...)).
//		Exec(ctx)
//
func (occb *ObClusterCreateBulk) OnConflictColumns(columns ...string) *ObClusterUpsertBulk {
	occb.conflict = append(occb.conflict, sql.ConflictColumns(columns...))
	return &ObClusterUpsertBulk{
		create: occb,
	}
}

// ObClusterUpsertBulk is the builder for "upsert"-ing
// a bulk of ObCluster nodes.
type ObClusterUpsertBulk struct {
	create *ObClusterCreateBulk
}

// UpdateNewValues updates the mutable fields using the new values that
// were set on create. Using this option is equivalent to using:
//
//	client.ObCluster.Create().
//		OnConflict(
//			sql.ResolveWithNewValues(),
//		).
//		Exec(ctx)
//
func (u *ObClusterUpsertBulk) UpdateNewValues() *ObClusterUpsertBulk {
	u.create.conflict = append(u.create.conflict, sql.ResolveWithNewValues())
	return u
}

// Ignore sets each column to itself in case of conflict.
// Using this option is equivalent to using:
//
//	client.ObCluster.Create().
//		OnConflict(sql.ResolveWithIgnore()).
//		Exec(ctx)
//
func (u *ObClusterUpsertBulk) Ignore() *ObClusterUpsertBulk {
	u.create.conflict = append(u.create.conflict, sql.ResolveWithIgnore())
	return u
}

// DoNothing configures the conflict_action to `DO NOTHING`.
// Supported only by SQLite and PostgreSQL.
func (u *ObClusterUpsertBulk) DoNothing() *ObClusterUpsertBulk {
	u.create.conflict = append(u.create.conflict, sql.DoNothing())
	return u
}

// Update allows overriding fields `UPDATE` values. See the ObClusterCreateBulk.OnConflict
// documentation for more info.
func (u *ObClusterUpsertBulk) Update(set func(*ObClusterUpsert)) *ObClusterUpsertBulk {
	u.create.conflict = append(u.create.conflict, sql.ResolveWith(func(update *sql.UpdateSet) {
		set(&ObClusterUpsert{UpdateSet: update})
	}))
	return u
}

// SetCreateTime sets the "create_time" field.
func (u *ObClusterUpsertBulk) SetCreateTime(v time.Time) *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.SetCreateTime(v)
	})
}

// UpdateCreateTime sets the "create_time" field to the value that was provided on create.
func (u *ObClusterUpsertBulk) UpdateCreateTime() *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.UpdateCreateTime()
	})
}

// SetUpdateTime sets the "update_time" field.
func (u *ObClusterUpsertBulk) SetUpdateTime(v time.Time) *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.SetUpdateTime(v)
	})
}

// UpdateUpdateTime sets the "update_time" field to the value that was provided on create.
func (u *ObClusterUpsertBulk) UpdateUpdateTime() *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.UpdateUpdateTime()
	})
}

// SetName sets the "name" field.
func (u *ObClusterUpsertBulk) SetName(v string) *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.SetName(v)
	})
}

// UpdateName sets the "name" field to the value that was provided on create.
func (u *ObClusterUpsertBulk) UpdateName() *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.UpdateName()
	})
}

// SetObClusterID sets the "ob_cluster_id" field.
func (u *ObClusterUpsertBulk) SetObClusterID(v int64) *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.SetObClusterID(v)
	})
}

// AddObClusterID adds v to the "ob_cluster_id" field.
func (u *ObClusterUpsertBulk) AddObClusterID(v int64) *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.AddObClusterID(v)
	})
}

// UpdateObClusterID sets the "ob_cluster_id" field to the value that was provided on create.
func (u *ObClusterUpsertBulk) UpdateObClusterID() *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.UpdateObClusterID()
	})
}

// SetType sets the "type" field.
func (u *ObClusterUpsertBulk) SetType(v string) *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.SetType(v)
	})
}

// UpdateType sets the "type" field to the value that was provided on create.
func (u *ObClusterUpsertBulk) UpdateType() *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.UpdateType()
	})
}

// SetRootserviceJSON sets the "rootservice_json" field.
func (u *ObClusterUpsertBulk) SetRootserviceJSON(v string) *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.SetRootserviceJSON(v)
	})
}

// UpdateRootserviceJSON sets the "rootservice_json" field to the value that was provided on create.
func (u *ObClusterUpsertBulk) UpdateRootserviceJSON() *ObClusterUpsertBulk {
	return u.Update(func(s *ObClusterUpsert) {
		s.UpdateRootserviceJSON()
	})
}

// Exec executes the query.
func (u *ObClusterUpsertBulk) Exec(ctx context.Context) error {
	for i, b := range u.create.builders {
		if len(b.conflict) != 0 {
			return fmt.Errorf("ent: OnConflict was set for builder %d. Set it on the ObClusterCreateBulk instead", i)
		}
	}
	if len(u.create.conflict) == 0 {
		return errors.New("ent: missing options for ObClusterCreateBulk.OnConflict")
	}
	return u.create.Exec(ctx)
}

// ExecX is like Exec, but panics if an error occurs.
func (u *ObClusterUpsertBulk) ExecX(ctx context.Context) {
	if err := u.create.Exec(ctx); err != nil {
		panic(err)
	}
}
