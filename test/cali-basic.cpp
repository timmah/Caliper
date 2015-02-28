// A basic Caliper instrumentation demo / test file

#include <Annotation.h>
#include <Caliper.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void begin_foo_op()
{
    // Begin "foo"->"fooing" and keep it alive past the end of the current C++ scope
    cali::Annotation("foo", cali::Annotation::KeepAlive).begin("fooing");
}

void end_foo_op()
{
    // Explicitly end innermost level of "foo" annotation
    cali::Annotation("foo").end();
}


void print_context()
{
    cali::Caliper* c   { cali::Caliper::instance() };

    vector<uint64_t> ctx(2 * c->num_attributes(), 0);

    // retrieve current context record
    const size_t ctxsize = c->pull_context(CALI_SCOPE_THREAD, ctx.data(), ctx.size());

    // for (auto const &q : c->unpack(ctx.data(), ctxsize))
    //     cout << q << "\n";

    cout << endl;
}


int main(int argc, char* argv[])
{
    // Declare "phase" annotation
    cali::Annotation phase("phase");

    // Begin scope of phase->"main"
    auto a1 = phase.begin("main");

    int count = argc > 1 ? atoi(argv[1]) : 4;

    // An annotation with a user-defined datatype

    struct my_weird_type {
        unsigned u = 42;
        char     c = 'c';
        float    f = 42.42;
    } my_weird_elem;

    auto a2 = cali::Annotation("mydata").set(CALI_TYPE_USR, &my_weird_elem, sizeof(my_weird_elem));

    {
        // Add new scope phase->"loop" under phase->"main" 
        auto a3 = phase.begin("loop");

        // Set "loopcount" annotation to 'count' in current C++ scope
        auto a4 = cali::Annotation("loopcount").set(count);

        // Declare "iteration" annotation, store entries explicitly as values
        cali::Annotation iteration("iteration", cali::Annotation::StoreAsValue);

        for (int i = 0; i < count; ++i) {
            // Set "iteration" annotation to current value of 'i'
            iteration.set(i);

            begin_foo_op();
            end_foo_op();
        }

        iteration.end();

        // "loop", "loopcount" and "iteration" annotations implicitly end here 
    }

    // implicitly end phase->"main"
}
