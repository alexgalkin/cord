/*
    Copyright 2016-2017, Felspar Co Ltd. http://www.kirit.com/f5
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include <f5/cord/tstring.hpp>
#include <f5/cord/unicode.hpp>
using namespace f5::literals;


// check_valid
static_assert(f5::check_valid(' '), "Space is a valid UTF32 code point");
static_assert(not f5::check_valid<void>(0xff'ff'ff), "0xff'ff'ff is not a valid code point");


// u8length
static_assert(f5::u8length(0) == 1, "Zero is still 1 byte long");
static_assert(f5::u8length(' ') == 1, "Space is 1 byte long");
static_assert(f5::u8length(0xa3) == 2, "Pounds are 2 bytes long");
static_assert(f5::u8length(0xe01) == 3, "Thai chickens are 3 bytes long");
static_assert(f5::u8length(0x1d11e) == 4, "The treble clef is 4 bytes long");


// u8encode
constexpr auto space = f5::u8encode(' ');
// u8decode
constexpr unsigned char x[1] = {'x'};
static_assert(f5::decode(x).first == 'x', "Expected x");
static_assert(f5::decode(x).second.size() == 0u, "Should have used it all");
constexpr unsigned char ae[2] = {0xC3, 0xA6};
static_assert(f5::decode(ae).first == 0xe6, "Expected x");
static_assert(f5::decode(ae).second.size() == 0u, "Should have used it all");
constexpr unsigned char bom[3] = {0xEF,0xBB,0xBF};
static_assert(f5::decode(bom).first == 0xfeff, "Expected the BOM");
static_assert(f5::decode(bom).second.size() == 0u, "Should have used it all");
constexpr unsigned char clef[4] = {0xF0, 0x9D, 0x84, 0x9E};
static_assert(f5::decode(clef).first == 0x1d11e, "Expected the Clef");
static_assert(f5::decode(clef).second.size() == 0u, "Should have used it all");

// UTF-16
static_assert(not f5::is_surrogate(' '), "Space");
static_assert(f5::is_surrogate(0xd834), "High char for treble clef");
static_assert(f5::is_surrogate(0xdd1e), "Low char for treble clef");
static_assert(not f5::is_surrogate(0xfffd), "Replacement char");

static_assert(f5::u16decode(0xd834, 0xdd1e) == 0x1d11e, "Treble clef");
static_assert(f5::u16decode<void>(0xdd1e, 0xd834) == 0xfffd, "Substituted");
