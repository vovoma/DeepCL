// Copyright Hugh Perkins 2015 hughperkins at gmail
//
// This Source Code Form is subject to the terms of the Mozilla Public License, 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "test/gtest_supp.h"

#include "SpeedTemplates.h"

using namespace std;
using namespace SpeedTemplates;

TEST( testSpeedTemplates, basicsubstitution ) {
    string source = "\n"
"        This is my {{avalue}} template.  It's {{secondvalue}}...\n"
"        Today's weather is {{weather}}.\n"
"    \n";

    Template mytemplate( source );
    mytemplate.setValue( "avalue", 3 );
    mytemplate.setValue( "secondvalue", 12.123f );
    mytemplate.setValue( "weather", "rain" );
    string result = mytemplate.render();
    cout << result << endl;
    string expectedResult = "\n"
"        This is my 3 template.  It's 12.123...\n"
"        Today's weather is rain.\n"
"    \n";
    EXPECT_EQ( expectedResult, result );
}
TEST( testSpeedTemplates, namemissing ) {
    string source = "\n"
"        This is my {{avalue}} template.\n"
"    \n";

    Template mytemplate( source );
    bool threw = false;
    try {
        string result = mytemplate.render();
    } catch( render_error &e ) {
        EXPECT_EQ( string("name avalue not defined"), e.what() );
        threw = true;
    }
    EXPECT_EQ( true, threw );
}
TEST( testSpeedTemplates, loop ) {
    string source = "\n"
"        {% for i in range(its) %}\n"
"            a[{{i}}] = image[{{i}}];\n"
"        {% endfor %}\n"
"    \n";

    Template mytemplate( source );
    mytemplate.setValue( "its", 3 );
    string result = mytemplate.render();
    cout << result << endl;
    string expectedResult = "\n"
"        \n"
"            a[0] = image[0];\n"
"        \n"
"            a[1] = image[1];\n"
"        \n"
"            a[2] = image[2];\n"
"        \n"
"    \n";
    EXPECT_EQ( expectedResult, result );
}

TEST( testSpeedTemplates, nestedloop ) {
    string source = "\n"
"{% for i in range(its) %}a[{{i}}] = image[{{i}}];\n"
"{% for j in range(2) %}b[{{j}}] = image[{{j}}];\n"
"{% endfor %}{% endfor %}\n"
"";

    Template mytemplate( source );
    mytemplate.setValue( "its", 3 );
    string result = mytemplate.render();
    cout << "[" << result << "]" << endl;
    string expectedResult = "\n"
"a[0] = image[0];\n"
"b[0] = image[0];\n"
"b[1] = image[1];\n"
"a[1] = image[1];\n"
"b[0] = image[0];\n"
"b[1] = image[1];\n"
"a[2] = image[2];\n"
"b[0] = image[0];\n"
"b[1] = image[1];\n"
"\n"
"";
    EXPECT_EQ( expectedResult, result );
}

