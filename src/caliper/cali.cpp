/// @cali.cpp
/// Caliper C interface implementation

#include "cali.h"

#include "Caliper.h"

using namespace cali;

//
// --- Attribute interface
//

cali_id_t 
cali_create_attribute(const char* name, cali_attr_type type, cali_attr_properties properties)
{
    Attribute a = Caliper::instance()->create_attribute(name, type, properties);
    return a.id();
}

cali_id_t
cali_find_attribute(const char* name)
{
    Attribute a = Caliper::instance()->get_attribute(name);
    return a.id();
}

//
// --- Context interface
//

size_t
cali_get_context_size(cali_context_scope_t scope)
{
    return Caliper::instance()->context_size(scope);
}

size_t
cali_pull_context(int scope, uint64_t* buf, size_t bufsize)
{
    return Caliper::instance()->pull_context(scope, buf, bufsize);
}

void
cali_push_context(int scope)
{
    return Caliper::instance()->push_context(scope);
}

//
// --- Environment interface
//

void*
cali_current_contextbuffer(cali_context_scope_t scope)
{
    return Caliper::instance()->current_contextbuffer(scope);
}

cali_err
cali_create_environment(void **new_env)
{
    *new_env = Caliper::instance()->create_contextbuffer();
    return CALI_SUCCESS;
}



//
// --- Annotation interface
//

cali_err
cali_begin(cali_id_t attr, const void* value, size_t size)
{
    Caliper* c = Caliper::instance();
    return c->begin(c->get_attribute(attr), value, size);
}

cali_err
cali_end(cali_id_t attr)
{
    Caliper* c = Caliper::instance();
    return c->end(c->get_attribute(attr));
}

cali_err  
cali_set(cali_id_t attr, const void* value, size_t size)
{
    Caliper* c = Caliper::instance();
    return c->set(c->get_attribute(attr), value, size);
}

//
// --- I/O interface
//

// cali_err
// cali_write_metadata(void)
// {
//     if (Caliper::instance()->write_metadata())
//         return CALI_SUCCESS;

//     return CALI_EINV;
// }
