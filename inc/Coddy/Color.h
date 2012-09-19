////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_COLORS_COLOR_H
#define CLODDY_API_UTIL_COLORS_COLOR_H

#include "CodeX/System.h"

// Declare class ::Cloddy::API::Util::Colors::Color.

namespace Cloddy { namespace API { namespace Util { namespace Colors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  The Color class provides operations on 32-bit ARGB color values.
   */
  class Color
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The color 'AliceBlue' (0xF0F8FF).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 AliceBlue = -984833;
    
    /*!
     * @brief  The color 'AntiqueWhite' (0xFAEBD7).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 AntiqueWhite = -332841;
    
    /*!
     * @brief  The color 'Aqua' (0x00FFFF).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Aqua = -16711681;
    
    /*!
     * @brief  The color 'Aquamarine' (0x7FFFD4).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Aquamarine = -8388652;
    
    /*!
     * @brief  The color 'Azure' (0xF0FFFF).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Azure = -983041;
    
    /*!
     * @brief  The color 'Beige' (0xF5F5DC).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Beige = -657956;
    
    /*!
     * @brief  The color 'Bisque' (0xFFE4C4).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Bisque = -6972;
    
    /*!
     * @brief  The color 'Black' (0x000000).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Black = -16777216;
    
    /*!
     * @brief  The color 'BlanchedAlmond' (0xFFEBCD).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 BlanchedAlmond = -5171;
    
    /*!
     * @brief  The color 'Blue' (0x0000FF).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Blue = -16776961;
    
    /*!
     * @brief  The color 'BlueViolet' (0x8A2BE2).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 BlueViolet = -7722014;
    
    /*!
     * @brief  The color 'Brown' (0xA52A2A).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Brown = -5952982;
    
    /*!
     * @brief  The color 'BurlyWood' (0xDEB887).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 BurlyWood = -2180985;
    
    /*!
     * @brief  The color 'CadetBlue' (0x5F9EA0).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 CadetBlue = -10510688;
    
    /*!
     * @brief  The color 'Chartreuse' (0x7FFF00).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Chartreuse = -8388864;
    
    /*!
     * @brief  The color 'Chocolate' (0xD2691E).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Chocolate = -2987746;
    
    /*!
     * @brief  The color 'Coral' (0xFF7F50).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Coral = -32944;
    
    /*!
     * @brief  The color 'CornflowerBlue' (0x6495ED).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 CornflowerBlue = -10185235;
    
    /*!
     * @brief  The color 'Cornsilk' (0xFFF8DC).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Cornsilk = -1828;
    
    /*!
     * @brief  The color 'Crimson' (0xDC143C).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Crimson = -2354116;
    
    /*!
     * @brief  The color 'Cyan' (0x00FFFF).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Cyan = -16711681;
    
    /*!
     * @brief  The color 'DarkBlue' (0x00008B).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkBlue = -16777077;
    
    /*!
     * @brief  The color 'DarkCyan' (0x008B8B).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkCyan = -16741493;
    
    /*!
     * @brief  The color 'DarkGoldenrod' (0xB8860B).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkGoldenrod = -4684277;
    
    /*!
     * @brief  The color 'DarkGray' (0xA9A9A9).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkGray = -5658199;
    
    /*!
     * @brief  The color 'DarkGreen' (0x006400).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkGreen = -16751616;
    
    /*!
     * @brief  The color 'DarkKhaki' (0xBDB76B).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkKhaki = -4343957;
    
    /*!
     * @brief  The color 'DarkMagenta' (0x8B008B).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkMagenta = -7667573;
    
    /*!
     * @brief  The color 'DarkOliveGreen' (0x556B2F).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkOliveGreen = -11179217;
    
    /*!
     * @brief  The color 'DarkOrange' (0xFF8C00).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkOrange = -29696;
    
    /*!
     * @brief  The color 'DarkOrchid' (0x9932CC).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkOrchid = -6737204;
    
    /*!
     * @brief  The color 'DarkRed' (0x8B0000).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkRed = -7667712;
    
    /*!
     * @brief  The color 'DarkSalmon' (0xE9967A).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkSalmon = -1468806;
    
    /*!
     * @brief  The color 'DarkSeaGreen' (0x8FBC8B).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkSeaGreen = -7357301;
    
    /*!
     * @brief  The color 'DarkSlateBlue' (0x483D8B).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkSlateBlue = -12042869;
    
    /*!
     * @brief  The color 'DarkSlateGray' (0x2F4F4F).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkSlateGray = -13676721;
    
    /*!
     * @brief  The color 'DarkTurquoise' (0x00CED1).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkTurquoise = -16724271;
    
    /*!
     * @brief  The color 'DarkViolet' (0x9400D3).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DarkViolet = -7077677;
    
    /*!
     * @brief  The color 'DeepPink' (0xFF1493).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DeepPink = -60269;
    
    /*!
     * @brief  The color 'DeepSkyBlue' (0x00BFFF).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DeepSkyBlue = -16728065;
    
    /*!
     * @brief  The color 'DimGray' (0x696969).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DimGray = -9868951;
    
    /*!
     * @brief  The color 'DodgerBlue' (0x1E90FF).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 DodgerBlue = -14774017;
    
    /*!
     * @brief  The color 'Firebrick' (0xB22222).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Firebrick = -5103070;
    
    /*!
     * @brief  The color 'FloralWhite' (0xFFFAF0).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 FloralWhite = -1296;
    
    /*!
     * @brief  The color 'ForestGreen' (0x228B22).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 ForestGreen = -14513374;
    
    /*!
     * @brief  The color 'Fuchsia' (0xFF00FF).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Fuchsia = -65281;
    
    /*!
     * @brief  The color 'Gainsboro' (0xDCDCDC).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Gainsboro = -2302756;
    
    /*!
     * @brief  The color 'GhostWhite' (0xF8F8FF).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 GhostWhite = -460545;
    
    /*!
     * @brief  The color 'Gold' (0xFFD700).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Gold = -10496;
    
    /*!
     * @brief  The color 'Goldenrod' (0xDAA520).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Goldenrod = -2448096;
    
    /*!
     * @brief  The color 'Gray' (0x808080).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Gray = -8355712;
    
    /*!
     * @brief  The color 'Green' (0x008000).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Green = -16744448;
    
    /*!
     * @brief  The color 'GreenYellow' (0xADFF2F).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 GreenYellow = -5374161;
    
    /*!
     * @brief  The color 'Honeydew' (0xF0FFF0).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Honeydew = -983056;
    
    /*!
     * @brief  The color 'HotPink' (0xFF69B4).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 HotPink = -38476;
    
    /*!
     * @brief  The color 'IndianRed' (0xCD5C5C).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 IndianRed = -3318692;
    
    /*!
     * @brief  The color 'Indigo' (0x4B0082).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Indigo = -11861886;
    
    /*!
     * @brief  The color 'Ivory' (0xFFFFF0).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Ivory = -16;
    
    /*!
     * @brief  The color 'Khaki' (0xF0E68C).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Khaki = -989556;
    
    /*!
     * @brief  The color 'Lavender' (0xE6E6FA).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Lavender = -1644806;
    
    /*!
     * @brief  The color 'LavenderBlush' (0xFFF0F5).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LavenderBlush = -3851;
    
    /*!
     * @brief  The color 'LawnGreen' (0x7CFC00).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LawnGreen = -8586240;
    
    /*!
     * @brief  The color 'LemonChiffon' (0xFFFACD).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LemonChiffon = -1331;
    
    /*!
     * @brief  The color 'LightBlue' (0xADD8E6).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightBlue = -5383962;
    
    /*!
     * @brief  The color 'LightCoral' (0xF08080).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightCoral = -1015680;
    
    /*!
     * @brief  The color 'LightCyan' (0xE0FFFF).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightCyan = -2031617;
    
    /*!
     * @brief  The color 'LightGoldenrodYellow' (0xFAFAD2).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightGoldenrodYellow = -329006;
    
    /*!
     * @brief  The color 'LightGray' (0xD3D3D3).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightGray = -2894893;
    
    /*!
     * @brief  The color 'LightGreen' (0x90EE90).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightGreen = -7278960;
    
    /*!
     * @brief  The color 'LightPink' (0xFFB6C1).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightPink = -18751;
    
    /*!
     * @brief  The color 'LightSalmon' (0xFFA07A).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightSalmon = -24454;
    
    /*!
     * @brief  The color 'LightSeaGreen' (0x20B2AA).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightSeaGreen = -14634326;
    
    /*!
     * @brief  The color 'LightSkyBlue' (0x87CEFA).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightSkyBlue = -7876870;
    
    /*!
     * @brief  The color 'LightSlateGray' (0x778899).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightSlateGray = -8943463;
    
    /*!
     * @brief  The color 'LightSteelBlue' (0xB0C4DE).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightSteelBlue = -5192482;
    
    /*!
     * @brief  The color 'LightYellow' (0xFFFFE0).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LightYellow = -32;
    
    /*!
     * @brief  The color 'Lime' (0x00FF00).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Lime = -16711936;
    
    /*!
     * @brief  The color 'LimeGreen' (0x32CD32).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 LimeGreen = -13447886;
    
    /*!
     * @brief  The color 'Linen' (0xFAF0E6).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Linen = -331546;
    
    /*!
     * @brief  The color 'Magenta' (0xFF00FF).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Magenta = -65281;
    
    /*!
     * @brief  The color 'Maroon' (0x800000).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Maroon = -8388608;
    
    /*!
     * @brief  The color 'MediumAquamarine' (0x66CDAA).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 MediumAquamarine = -10039894;
    
    /*!
     * @brief  The color 'MediumBlue' (0x0000CD).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 MediumBlue = -16777011;
    
    /*!
     * @brief  The color 'MediumOrchid' (0xBA55D3).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 MediumOrchid = -4565549;
    
    /*!
     * @brief  The color 'MediumPurple' (0x9370DB).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 MediumPurple = -7114533;
    
    /*!
     * @brief  The color 'MediumSeaGreen' (0x3CB371).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 MediumSeaGreen = -12799119;
    
    /*!
     * @brief  The color 'MediumSlateBlue' (0x7B68EE).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 MediumSlateBlue = -8689426;
    
    /*!
     * @brief  The color 'MediumSpringGreen' (0x00FA9A).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 MediumSpringGreen = -16713062;
    
    /*!
     * @brief  The color 'MediumTurquoise' (0x48D1CC).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 MediumTurquoise = -12004916;
    
    /*!
     * @brief  The color 'MediumVioletRed' (0xC71585).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 MediumVioletRed = -3730043;
    
    /*!
     * @brief  The color 'MidnightBlue' (0x191970).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 MidnightBlue = -15132304;
    
    /*!
     * @brief  The color 'MintCream' (0xF5FFFA).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 MintCream = -655366;
    
    /*!
     * @brief  The color 'MistyRose' (0xFFE4E1).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 MistyRose = -6943;
    
    /*!
     * @brief  The color 'Moccasin' (0xFFE4B5).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Moccasin = -6987;
    
    /*!
     * @brief  The color 'NavajoWhite' (0xFFDEAD).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 NavajoWhite = -8531;
    
    /*!
     * @brief  The color 'Navy' (0x000080).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Navy = -16777088;
    
    /*!
     * @brief  The color 'OldLace' (0xFDF5E6).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 OldLace = -133658;
    
    /*!
     * @brief  The color 'Olive' (0x808000).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Olive = -8355840;
    
    /*!
     * @brief  The color 'OliveDrab' (0x6B8E23).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 OliveDrab = -9728477;
    
    /*!
     * @brief  Bitmask for reducing the opacity of a fully opaque color to 0%.
     */
    static const int32 Opaque0 = 0xFFFFFF;
    
    /*!
     * @brief  Bitmask for setting the opacity of a fully opaque color to 100%.
     * 
     * <pre>
     *     result = color | Opaque100;
     * </pre>
     */
    static const int32 Opaque100 = 255 << 24;
    
    /*!
     * @brief  Bitmask for reducing the opacity of a fully opaque color to 25%.
     */
    static const int32 Opaque25 = 64 << 24 | 0xFFFFFF;
    
    /*!
     * @brief  Bitmask for reducing the opacity of a fully opaque color to 50%.
     */
    static const int32 Opaque50 = 128 << 24 | 0xFFFFFF;
    
    /*!
     * @brief  Bitmask for reducing the opacity of a fully opaque color to 75%.
     */
    static const int32 Opaque75 = (128 + 64) << 24 | 0xFFFFFF;
    
    /*!
     * @brief  The color 'Orange' (0xFFA500).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Orange = -23296;
    
    /*!
     * @brief  The color 'OrangeRed' (0xFF4500).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 OrangeRed = -47872;
    
    /*!
     * @brief  The color 'Orchid' (0xDA70D6).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Orchid = -2461482;
    
    /*!
     * @brief  The color 'PaleGoldenrod' (0xEEE8AA).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 PaleGoldenrod = -1120086;
    
    /*!
     * @brief  The color 'PaleGreen' (0x98FB98).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 PaleGreen = -6751336;
    
    /*!
     * @brief  The color 'PaleTurquoise' (0xAFEEEE).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 PaleTurquoise = -5247250;
    
    /*!
     * @brief  The color 'PaleVioletRed' (0xDB7093).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 PaleVioletRed = -2396013;
    
    /*!
     * @brief  The color 'PapayaWhip' (0xFFEFD5).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 PapayaWhip = -4139;
    
    /*!
     * @brief  The color 'PeachPuff' (0xFFDAB9).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 PeachPuff = -9543;
    
    /*!
     * @brief  The color 'Peru' (0xCD853F).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Peru = -3308225;
    
    /*!
     * @brief  The color 'Pink' (0xFFC0CB).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Pink = -16181;
    
    /*!
     * @brief  The color 'Plum' (0xDDA0DD).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Plum = -2252579;
    
    /*!
     * @brief  The color 'PowderBlue' (0xB0E0E6).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 PowderBlue = -5185306;
    
    /*!
     * @brief  The color 'Purple' (0x800080).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Purple = -8388480;
    
    /*!
     * @brief  The color 'Red' (0xFF0000).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Red = -65536;
    
    /*!
     * @brief  The color 'RosyBrown' (0xBC8F8F).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 RosyBrown = -4419697;
    
    /*!
     * @brief  The color 'RoyalBlue' (0x4169E1).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 RoyalBlue = -12490271;
    
    /*!
     * @brief  The color 'SaddleBrown' (0x8B4513).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 SaddleBrown = -7650029;
    
    /*!
     * @brief  The color 'Salmon' (0xFA8072).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Salmon = -360334;
    
    /*!
     * @brief  The color 'SandyBrown' (0xF4A460).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 SandyBrown = -744352;
    
    /*!
     * @brief  The color 'SeaGreen' (0x2E8B57).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 SeaGreen = -13726889;
    
    /*!
     * @brief  The color 'SeaShell' (0xFFF5EE).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 SeaShell = -2578;
    
    /*!
     * @brief  The color 'Sienna' (0xA0522D).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Sienna = -6270419;
    
    /*!
     * @brief  The color 'Silver' (0xC0C0C0).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Silver = -4144960;
    
    /*!
     * @brief  The color 'SkyBlue' (0x87CEEB).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 SkyBlue = -7876885;
    
    /*!
     * @brief  The color 'SlateBlue' (0x6A5ACD).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 SlateBlue = -9807155;
    
    /*!
     * @brief  The color 'SlateGray' (0x708090).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 SlateGray = -9404272;
    
    /*!
     * @brief  The color 'Snow' (0xFFFAFA).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Snow = -1286;
    
    /*!
     * @brief  The color 'SpringGreen' (0x00FF7F).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 SpringGreen = -16711809;
    
    /*!
     * @brief  The color 'SteelBlue' (0x4682B4).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 SteelBlue = -12156236;
    
    /*!
     * @brief  The color 'Tan' (0xD2B48C).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Tan = -2968436;
    
    /*!
     * @brief  The color 'Teal' (0x008080).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Teal = -16744320;
    
    /*!
     * @brief  The color 'Thistle' (0xD8BFD8).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Thistle = -2572328;
    
    /*!
     * @brief  The color 'Tomato' (0xFF6347).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Tomato = -40121;
    
    /*!
     * @brief  The color 'Transparent' (0xFFFFFF,alpha 0x00).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Transparent = 16777215;
    
    /*!
     * @brief  The color 'Turquoise' (0x40E0D0).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Turquoise = -12525360;
    
    /*!
     * @brief  The color 'Violet' (0xEE82EE).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Violet = -1146130;
    
    /*!
     * @brief  The color 'Wheat' (0xF5DEB3).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Wheat = -663885;
    
    /*!
     * @brief  The color 'White' (0xFFFFFF).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 White = -1;
    
    /*!
     * @brief  The color 'WhiteSmoke' (0xF5F5F5).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 WhiteSmoke = -657931;
    
    /*!
     * @brief  The color 'Yellow' (0xFFFF00).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 Yellow = -256;
    
    /*!
     * @brief  The color 'YellowGreen' (0x9ACD32).
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    static const int32 YellowGreen = -6632142;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds the given color values.
     * 
     * @param a First color value.
     * @param b Second color value.
     * 
     * @return The resulting color value.
     */
    static int32 Add(int32 a, int32 b);
    
    /*!
     * @brief  Returns the alpha channel of the given color value.
     * 
     * @param color The 32-bit ARGB color value
     * 
     * @return <b>[0..1]</b>  The floating point channel value.
     */
    static float32 AlphaF(int32 color);
    
    /*!
     * @brief  Returns the alpha channel of the given color value.
     * 
     * @param color The 32-bit ARGB color value
     * 
     * @return <b>[0..255]</b>  The channel value.
     */
    static int32 AlphaI(int32 color);
    
    /*!
     * @brief  Blends the given colors using the specified blend factor.
     * 
     * @param a First color to blend.
     * @param b Second color to blend.
     * @param factor The blend factor.
     * 
     * @return The resulting color.
     */
    static int32 Blend(int32 a, int32 b, float64 factor);
    
    /*!
     * @brief  Blends the given colors using the specified blend factor.
     * 
     * @param a First color to blend.
     * @param b Second color to blend.
     * @param c Third color to blend.
     * @param factor1 The first blend factor in the range <c>[0..255]</c>.
     * @param factor2 The second blend factor in the range <c>[0..255]</c>.
     * 
     * @return The resulting color.
     */
    static int32 Blend(int32 a, int32 b, int32 c, int32 factor1, int32 factor2);
    
    /*!
     * @brief  Blends the given colors using the specified blend factor.
     * 
     * @param a First color to blend.
     * @param b Second color to blend.
     * @param factor The blend factor in the range <c>[0..255]</c>.
     * 
     * @return The resulting color.
     */
    static int32 Blend(int32 a, int32 b, int32 factor);
    
    /*!
     * @brief  Returns the blue channel of the given color value.
     * 
     * @param color The 32-bit ARGB color value
     * 
     * @return <b>[0..1]</b>  The floating point channel value.
     */
    static float32 BlueF(int32 color);
    
    /*!
     * @brief  Returns the blue channel of the given color value.
     * 
     * @param color The 32-bit ARGB color value
     * 
     * @return <b>[0..255]</b>  The channel value.
     */
    static int32 BlueI(int32 color);
    
    /*!
     * @brief  Decodes the given 15-bit RGB 555 color value.
     * 
     * @param color The color value to decode.
     * 
     * @return The 32-bit ARGB 8888 color value.
     */
    static int32 Decode555(int32 color);
    
    /*!
     * @brief  Decodes the given 16-bit RGB 565 color value.
     * 
     * @param color The color value to decode.
     * 
     * @return The 32-bit ARGB 8888 color value.
     */
    static int32 Decode565(int32 color);
    
    /*!
     * @brief  Encodes the given 32-bit ARGB 8888 color value.
     * 
     * @param color The color value to encode.
     * 
     * @return The 15-bit RGB 555 color value.
     */
    static int32 Encode555(int32 color);
    
    /*!
     * @brief  Encodes the given 32-bit ARGB 8888 color value.
     * 
     * @param color The color value to encode.
     * 
     * @return The 16-bit RGB 565 color value.
     */
    static int32 Encode565(int32 color);
    
    /*!
     * @brief  Converts a color value from HSV to RGB.
     * 
     * The mapping from RGB colors to HSV colors is bijective:Colors can be translated between RGB 
     * and HSV using the #ToHSV,#FromHSV(int32) and #FromHSV(int32,int32,int32) methods without 
     * loss in precision.
     * 
     * The HSV color value is a 32-bit integer:Bits 0-7 represent the brightness value in the range 
     * <c>[0..255]</c>,Bits 8-15 represent the saturation value in the range <c>[0..255]</c> and 
     * Bits 16 - 26 represent the hue value in the range <c>[0..1536]</c> with 
     * <c>1536 :=360 degrees</c>.
     * 
     * @param color The HSV color value.
     * 
     * @return The RGB color value.
     */
    static int32 FromHSV(int32 color);
    
    /*!
     * @brief  Converts a color value from HSV to RGB.
     * 
     * The mapping from RGB colors to HSV colors is bijective:Colors can be translated between RGB 
     * and HSV using the #ToHSV,#FromHSV(int32) and #FromHSV(int32,int32,int32) methods without 
     * loss in precision.
     * 
     * @param hue Hue value in range [0..1535](1536 :=360 degrees).
     * @param saturation Saturation value in range [0..255].
     * @param brightness Brightness value in range [0..255].
     * 
     * @return The RGB color value.
     */
    static int32 FromHSV(int32 hue, int32 saturation, int32 brightness);
    
    /*!
     * @brief  Creates a color based on the given color channel values.
     * 
     * The alpha channel is set ot \c 255 .All other channels are clamped to [0..255].
     * 
     * @param red Red channel value in range.
     * @param green Green channel value.
     * @param blue Blue channel value.
     * 
     * @return The color.
     */
    static int32 FromRGB(int32 red, int32 green, int32 blue);
    
    /*!
     * @brief  Creates a color based on the given color channel values.
     * 
     * All channels are clamped to [0..255].
     * 
     * @param alpha Alpha channel value.
     * @param red Red channel value in range.
     * @param green Green channel value.
     * @param blue Blue channel value.
     * 
     * @return The color.
     */
    static int32 FromRGB(int32 alpha, int32 red, int32 green, int32 blue);
    
    /*!
     * @brief  Returns the green channel of the given color value.
     * 
     * @param color The 32-bit ARGB color value
     * 
     * @return <b>[0..1]</b>  The floating point channel value.
     */
    static float32 GreenF(int32 color);
    
    /*!
     * @brief  Returns the green channel of the given color value.
     * 
     * @param color The 32-bit ARGB color value
     * 
     * @return <b>[0..255]</b>  The channel value.
     */
    static int32 GreenI(int32 color);
    
    /*!
     * @brief  Computes the component wise maximum of the given color values.
     * 
     * @param a First color value.
     * @param b Second color value.
     * 
     * @return The resulting color value.
     */
    static int32 Maximum(int32 a, int32 b);
    
    /*!
     * @brief  Computes the component wise minimum of the given color values.
     * 
     * @param a First color value.
     * @param b Second color value.
     * 
     * @return The resulting color value.
     */
    static int32 Minimum(int32 a, int32 b);
    
    /*!
     * @brief  Mixes the given color values using a blend factor of <c>0.5</c>.
     * 
     * @param a First color value.
     * @param b Second color value.
     * 
     * @return The resulting color value.
     */
    static int32 Mix(int32 a, int32 b);
    
    /*!
     * @brief  Mixes the first and second color value using a Catmull-Rom spline.
     * 
     * @param argbA Zeroth float value.
     * @param argbB First float value.
     * @param argbC Second float value.
     * @param argbD Third float value.
     * @param f Mix factor in the range <c>[0..65536]</c>.
     * 
     * @return The mixed value.
     */
    static int32 Mix(int32 argbA, int32 argbB, int32 argbC, int32 argbD, int32 f);
    
    /*!
     * @brief  Modifies the given color in \e HSV  space and returns the resulting color.
     * 
     * @param color The input color.
     * @param hueDelta The hue delta.
     * @param saturationDelta The saturation delta.
     * @param valueDelta The value delta.
     * 
     * @return The resulting color.
     */
    static int32 ModifyHSV(int32 color, int32 hueDelta, int32 saturationDelta, int32 valueDelta);
    
    /*!
     * @brief  Modifies the given color in \e HSV  space and returns the resulting color.
     * 
     * @param color The input color.
     * @param hueDelta The hue delta.
     * 
     * @return The resulting color.
     */
    static int32 ModifyHue(int32 color, int32 hueDelta);
    
    /*!
     * @brief  Modifies the given color in \e HSV  space and returns the resulting color.
     * 
     * @param color The input color.
     * @param saturationDelta The saturation delta.
     * 
     * @return The resulting color.
     */
    static int32 ModifySaturation(int32 color, int32 saturationDelta);
    
    /*!
     * @brief  Modifies the given color in \e HSV  space and returns the resulting color.
     * 
     * @param color The input color.
     * @param valueDelta The value delta.
     * 
     * @return The resulting color.
     */
    static int32 ModifyValue(int32 color, int32 valueDelta);
    
    /*!
     * @brief  Modulates the given color values.
     * 
     * @param a First color value.
     * @param b Second color value.
     * 
     * @return The resulting color value.
     */
    static int32 Modulate(int32 a, int32 b);
    
    /*!
     * @brief  Replaces the alpha component of the given color.
     * 
     * @param color The color.
     * @param alpha The new alpha channel.
     * 
     * @return The resulting color.
     */
    static int32 Opaque(int32 color, int32 alpha);
    
    /*!
     * @brief  Returns the red channel of the given color value.
     * 
     * @param color The 32-bit ARGB color value
     * 
     * @return <b>[0..1]</b>  The floating point channel value.
     */
    static float32 RedF(int32 color);
    
    /*!
     * @brief  Returns the red channel of the given color value.
     * 
     * @param color The 32-bit ARGB color value
     * 
     * @return <b>[0..255]</b>  The channel value.
     */
    static int32 RedI(int32 color);
    
    /*!
     * @brief  Scales the given color value.
     * 
     * @param color The color value.
     * @param factor The scale factor.
     * 
     * @return The resulting color.
     */
    static int32 Scale(int32 color, float32 factor);
    
    /*!
     * @brief  Subtracts the second color value from the first one.
     * 
     * @param a First color value.
     * @param b Second color value.
     * 
     * @return The resulting color value.
     */
    static int32 Subtract(int32 a, int32 b);
    
    /*!
     * @brief  Converts the given 32-bit ARGB color value to 8-bit grayscale.
     * 
     * @param color The 32-bit ARGB color value.
     * 
     * @return <b>[0..255]</b>  The 8-bit grayscale value.
     */
    static int32 ToGrayscale(int32 color);
    
    /*!
     * @brief  Converts this color value from RGB to HSV.
     * 
     * The mapping from RGB colors to HSV colors is bijective:Colors can be translated between RGB 
     * and HSV using the #ToHSV,#FromHSV(int32) and #FromHSV(int32,int32,int32)methods without loss 
     * in precision.
     * 
     * The HSV color value is returned as a 32-bit integer:Bits 0-7 represent the brightness value 
     * in the range <c>[0..255]</c>,Bits 8-15 represent the saturation value in the range 
     * <c>[0..255]</c> and Bits 16 - 26 represent the hue value in the range <c>[0..1536]</c> with 
     * <c>1536 :=360 degrees</c>.
     * 
     * @param color The RGB color value.
     * 
     * @return The HSV color value.
     */
    static int32 ToHSV(int32 color);
  };
  
} } } } 

#endif
