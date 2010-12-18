#include "TestGluonCore.h"

#include "../core/gdlhandler.h"

#include <cassert>
#include <cstddef>

using namespace GluonCore;

void TestGluonCore::basicSerialization()
{
    const char* test =
        "{ GluonCore::GluonObject(AnotherObject)\n"
        "reference GluonCore::GluonObject(AnObject/AChildObject)\n"
        "}\n"
        "{ GluonCore::GluonObject(AnObject)\n"
        "{ GluonCore::GluonObject(AChildObject)\n"
        "}\n"
        "}"
    ;

    QVERIFY(ensure_reversible(test));
}

