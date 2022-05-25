﻿/*
 * SPDX-FileCopyrightText: 2017~2017 CSSlayer <wengxt@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */
#include "glo.h"
#include "imelog.h"

#include <DPinyin>
DCORE_USE_NAMESPACE

QMap<QString, QString> g_uniqueNameToEnglishMap;
QMap<QString, QString> g_uniqueNameToChineseMap;

FcitxQtStringKeyValueList g_useIMList;
int g_maxLanguageIndex = 0;

int g_currentIMViewIndex = 0;

typedef struct s_languageList {
    char uniqueName[64];
    char chineseName[64];
    char englishName[64];
} s_languageList;

s_languageList languageList[] = {
	{"keyboard-vn-qderty", "越南语", "Vietnamese"},
	{"keyboard-vn", "越南语", "Vietnamese"},
	{"keyboard-vn-fr", "越南语", "Vietnamese"},
	{"keyboard-vn-us", "越南语", "Vietnamese"},
	{"keyboard-vn-aderty", "越南语", "Vietnamese"},
	{"keyboard-gb", "英语", "English"},
	{"keyboard-gb-colemak", "英语", "English"},
	{"keyboard-gb-pl", "英语", "English"},
	{"keyboard-gb-dvorakukp", "英语", "English"},
	{"keyboard-gb-extd", "英语", "English"},
	{"keyboard-gb-mac_intl", "英语", "English"},
	{"keyboard-gb-dvorak", "英语", "English"},
	{"keyboard-gb-mac", "英语", "English"},
	{"keyboard-gb-intl", "英语", "English"},
	{"keyboard-gb-sun_type6", "英语", "English"},
	{"keyboard-ng", "英语", "English"},
	{"keyboard-ng-hausa", "英语", "English"},
	{"keyboard-ng-yoruba", "英语", "English"},
	{"keyboard-ng-igbo", "英语", "English"},
	{"keyboard-za", "英语", "English"},
	{"keyboard-us", "英语", "English"},
	{"keyboard-us-crd", "英语", "English"},
	{"keyboard-us-norman", "英语", "English"},
	{"keyboard-us-chr", "英语", "English"},
	{"keyboard-us-dvorak-classic", "英语", "English"},
	{"keyboard-us-carpalx-full-intl", "英语", "English"},
	{"keyboard-us-sun_type6", "英语", "English"},
	{"keyboard-us-altgr-intl", "英语", "English"},
	{"keyboard-us-dvorak-r", "英语", "English"},
	{"keyboard-us-dvorak-alt-intl", "英语", "English"},
	{"keyboard-us-intl", "英语", "English"},
	{"keyboard-us-dvorak", "英语", "English"},
	{"keyboard-us-intl-unicode", "英语", "English"},
	{"keyboard-us-euro", "英语", "English"},
	{"keyboard-us-alt-intl", "英语", "English"},
	{"keyboard-us-colemak", "英语", "English"},
	{"keyboard-us-dvorak-intl", "英语", "English"},
	{"keyboard-us-dvorak-l", "英语", "English"},
	{"keyboard-us-dvp", "英语", "English"},
	{"keyboard-us-rus", "英语", "English"},
	{"keyboard-us-mac", "英语", "English"},
	{"keyboard-us-hbs", "英语", "English"},
	{"keyboard-us-workman", "英语", "English"},
	{"keyboard-us-workman-intl", "英语", "English"},
	{"keyboard-us-alt-intl-unicode", "英语", "English"},
	{"keyboard-us-ats", "英语", "English"},
	{"keyboard-us-ibm238l", "英语", "English"},
	{"keyboard-us-carpalx", "英语", "English"},
	{"keyboard-us-carpalx-intl", "英语", "English"},
	{"keyboard-us-carpalx-altgr-intl", "英语", "English"},
	{"keyboard-us-carpalx-full", "英语", "English"},
	{"keyboard-us-carpalx-full-altgr-intl", "英语", "English"},
	{"keyboard-us-scn", "英语", "English"},
	{"keyboard-us-cz_sk_de", "英语", "English"},
	{"keyboard-us-olpc2", "英语", "English"},
	{"keyboard-gh", "英语", "English"},
	{"keyboard-gh-fula", "英语", "English"},
	{"keyboard-gh-hausa", "英语", "English"},
	{"keyboard-gh-generic", "英语", "English"},
	{"keyboard-gh-ewe", "英语", "English"},
	{"keyboard-gh-ga", "英语", "English"},
	{"keyboard-gh-gillbt", "英语", "English"},
	{"keyboard-gh-akan", "英语", "English"},
	{"keyboard-gh-avn", "英语", "English"},
	{"keyboard-cm", "英语", "English"},
	{"keyboard-cm-french", "英语", "English"},
	{"keyboard-cm-mmuock", "英语", "English"},
	{"keyboard-cm-dvorak", "英语", "English"},
	{"keyboard-cm-qwerty", "英语", "English"},
	{"keyboard-cm-azerty", "英语", "English"},
	{"keyboard-au", "英语", "English"},
	{"keyboard-id", "印尼语", "Indonesian"},
	{"keyboard-in", "印地语", "Hindi"},
	{"keyboard-in-guru", "印地语", "Hindi"},
	{"keyboard-in-ben_probhat", "印地语", "Hindi"},
	{"keyboard-in-kan-kagapa", "印地语", "Hindi"},
	{"keyboard-in-tel-kagapa", "印地语", "Hindi"},
	{"keyboard-in-kan", "印地语", "Hindi"},
	{"keyboard-in-hin-wx", "印地语", "Hindi"},
	{"keyboard-in-urd-winkeys", "印地语", "Hindi"},
	{"keyboard-in-tam_tamilnet", "印地语", "Hindi"},
	{"keyboard-in-olck", "印地语", "Hindi"},
	{"keyboard-in-ori", "印地语", "Hindi"},
	{"keyboard-in-eeyek", "印地语", "Hindi"},
	{"keyboard-in-ben", "印地语", "Hindi"},
	{"keyboard-in-ben_baishakhi", "印地语", "Hindi"},
	{"keyboard-in-ben_bornona", "印地语", "Hindi"},
	{"keyboard-in-guj", "印地语", "Hindi"},
	{"keyboard-in-jhelum", "印地语", "Hindi"},
	{"keyboard-in-mal", "印地语", "Hindi"},
	{"keyboard-in-mal_lalitha", "印地语", "Hindi"},
	{"keyboard-in-mal_enhanced", "印地语", "Hindi"},
	{"keyboard-in-tam_tamilnet_with_tam_nums", "印地语", "Hindi"},
	{"keyboard-in-tam_tamilnet_TAB", "印地语", "Hindi"},
	{"keyboard-in-tam_tamilnet_TSCII", "印地语", "Hindi"},
	{"keyboard-in-tel", "印地语", "Hindi"},
	{"keyboard-in-tel-sarala", "印地语", "Hindi"},
	{"keyboard-in-urd-phonetic", "印地语", "Hindi"},
	{"keyboard-in-ben_gitanjali", "印地语", "Hindi"},
	{"keyboard-in-urd-phonetic3", "印地语", "Hindi"},
	{"keyboard-in-bolnagri", "印地语", "Hindi"},
	{"keyboard-in-hin-kagapa", "印地语", "Hindi"},
	{"keyboard-in-san-kagapa", "印地语", "Hindi"},
	{"keyboard-in-mar-kagapa", "印地语", "Hindi"},
	{"keyboard-in-eng", "印地语", "Hindi"},
	{"keyboard-in-ben_inscript", "印地语", "Hindi"},
	{"keyboard-in-tam", "印地语", "Hindi"},
	{"keyboard-it", "意大利语", "Italian"},
	{"keyboard-it-sun_type6", "意大利语", "Italian"},
	{"keyboard-it-ibm", "意大利语", "Italian"},
	{"keyboard-it-geo", "意大利语", "Italian"},
	{"keyboard-it-us", "意大利语", "Italian"},
	{"keyboard-it-nodeadkeys", "意大利语", "Italian"},
	{"keyboard-it-fur", "意大利语", "Italian"},
	{"keyboard-it-mac", "意大利语", "Italian"},
	{"keyboard-it-winkeys", "意大利语", "Italian"},
	{"keyboard-it-lld", "意大利语", "Italian"},
	{"keyboard-it-scn", "意大利语", "Italian"},
	{"keyboard-it-intl", "意大利语", "Italian"},
	{"keyboard-iq", "伊拉克", "Iraqi"},
	{"keyboard-iq-ku_ara", "伊拉克", "Iraqi"},
	{"keyboard-iq-ku_alt", "伊拉克", "Iraqi"},
	{"keyboard-iq-ku", "伊拉克", "Iraqi"},
	{"keyboard-iq-ku_f", "伊拉克", "Iraqi"},
	{"keyboard-am", "亚美尼亚语", "Armenian"},
	{"keyboard-am-eastern", "亚美尼亚语", "Armenian"},
	{"keyboard-am-phonetic-alt", "亚美尼亚语", "Armenian"},
	{"keyboard-am-eastern-alt", "亚美尼亚语", "Armenian"},
	{"keyboard-am-western", "亚美尼亚语", "Armenian"},
	{"keyboard-am-olpc-phonetic", "亚美尼亚语", "Armenian"},
	{"keyboard-am-phonetic", "亚美尼亚语", "Armenian"},
	{"keyboard-hu", "匈牙利", "Hungarian"},
	{"keyboard-hu-oldhun", "匈牙利", "Hungarian"},
	{"keyboard-hu-102_qwerty_dot_nodead", "匈牙利", "Hungarian"},
	{"keyboard-hu-102_qwerty_dot_dead", "匈牙利", "Hungarian"},
	{"keyboard-hu-102_qwerty_comma_nodead", "匈牙利", "Hungarian"},
	{"keyboard-hu-102_qwertz_dot_nodead", "匈牙利", "Hungarian"},
	{"keyboard-hu-101_qwerty_dot_nodead", "匈牙利", "Hungarian"},
	{"keyboard-hu-101_qwerty_dot_dead", "匈牙利", "Hungarian"},
	{"keyboard-hu-101_qwertz_dot_nodead", "匈牙利", "Hungarian"},
	{"keyboard-hu-101_qwertz_dot_dead", "匈牙利", "Hungarian"},
	{"keyboard-hu-101_qwertz_comma_dead", "匈牙利", "Hungarian"},
	{"keyboard-hu-qwerty", "匈牙利", "Hungarian"},
	{"keyboard-hu-nodeadkeys", "匈牙利", "Hungarian"},
	{"keyboard-hu-standard", "匈牙利", "Hungarian"},
	{"keyboard-hu-101_qwerty_comma_nodead", "匈牙利", "Hungarian"},
	{"keyboard-hu-102_qwertz_comma_nodead", "匈牙利", "Hungarian"},
	{"keyboard-hu-102_qwertz_dot_dead", "匈牙利", "Hungarian"},
	{"keyboard-hu-102_qwertz_comma_dead", "匈牙利", "Hungarian"},
	{"keyboard-hu-102_qwerty_comma_dead", "匈牙利", "Hungarian"},
	{"keyboard-hu-101_qwertz_comma_nodead", "匈牙利", "Hungarian"},
	{"keyboard-hu-101_qwerty_comma_dead", "匈牙利", "Hungarian"},
	{"keyboard-gr", "希腊语", "Greek"},
	{"keyboard-gr-colemak", "希腊语", "Greek"},
	{"keyboard-gr-sun_type6", "希腊语", "Greek"},
	{"keyboard-gr-extended", "希腊语", "Greek"},
	{"keyboard-gr-simple", "希腊语", "Greek"},
	{"keyboard-gr-nodeadkeys", "希腊语", "Greek"},
	{"keyboard-gr-nic", "希腊语", "Greek"},
	{"keyboard-il", "希伯来语", "Hebrew"},
	{"keyboard-il-biblicalSIL", "希伯来语", "Hebrew"},
	{"keyboard-il-phonetic", "希伯来语", "Hebrew"},
	{"keyboard-il-lyx", "希伯来语", "Hebrew"},
	{"keyboard-il-biblical", "希伯来语", "Hebrew"},
	{"keyboard-latam", "西班牙", "Spanish"},
	{"keyboard-latam-colemak", "西班牙", "Spanish"},
	{"keyboard-latam-sundeadkeys", "西班牙", "Spanish"},
	{"keyboard-latam-colemak-gaming", "西班牙", "Spanish"},
	{"keyboard-latam-dvorak", "西班牙", "Spanish"},
	{"keyboard-latam-nodeadkeys", "西班牙", "Spanish"},
	{"keyboard-latam-deadtilde", "西班牙", "Spanish"},
	{"keyboard-es-sun_type6", "西班牙", "Spanish"},
	{"keyboard-es-mac", "西班牙", "Spanish"},
	{"keyboard-es-ast", "西班牙", "Spanish"},
	{"keyboard-es-dvorak", "西班牙", "Spanish"},
	{"keyboard-es", "西班牙", "Spanish"},
	{"keyboard-es-deadtilde", "西班牙", "Spanish"},
	{"keyboard-es-cat", "西班牙", "Spanish"},
	{"keyboard-es-sundeadkeys", "西班牙", "Spanish"},
	{"keyboard-es-winkeys", "西班牙", "Spanish"},
	{"keyboard-es-nodeadkeys", "西班牙", "Spanish"},
	{"keyboard-uz", "乌兹别克语", "Uzbek"},
	{"keyboard-uz-latin", "乌兹别克语", "Uzbek"},
	{"keyboard-ua", "乌克兰语", "Ukrainian"},
	{"keyboard-ua-sun_type6", "乌克兰语", "Ukrainian"},
	{"keyboard-ua-typewriter", "乌克兰语", "Ukrainian"},
	{"keyboard-ua-phonetic", "乌克兰语", "Ukrainian"},
	{"keyboard-ua-legacy", "乌克兰语", "Ukrainian"},
	{"keyboard-ua-rstu", "乌克兰语", "Ukrainian"},
	{"keyboard-ua-rstu_ru", "乌克兰语", "Ukrainian"},
	{"keyboard-ua-homophonic", "乌克兰语", "Ukrainian"},
	{"keyboard-ua-winkeys", "乌克兰语", "Ukrainian"},
	{"keyboard-pk", "乌尔都语", "Urdu"},
	{"keyboard-pk-snd", "乌尔都语", "Urdu"},
	{"keyboard-pk-urd-crulp", "乌尔都语", "Urdu"},
	{"keyboard-pk-ara", "乌尔都语", "Urdu"},
	{"keyboard-pk-urd-nla", "乌尔都语", "Urdu"},
	{"keyboard-sn", "沃洛夫语", "Wolof"},
	{"keyboard-tm", "土库曼语", "Turkmen"},
	{"keyboard-tm-alt", "土库曼语", "Turkmen"},
	{"keyboard-tr-crh_alt", "土耳其", "Turkish"},
	{"keyboard-tr-intl", "土耳其", "Turkish"},
	{"keyboard-tr-ku_alt", "土耳其", "Turkish"},
	{"keyboard-tr-ku_f", "土耳其", "Turkish"},
	{"keyboard-tr-ku", "土耳其", "Turkish"},
	{"keyboard-tr-sundeadkeys", "土耳其", "Turkish"},
	{"keyboard-tr-alt", "土耳其", "Turkish"},
	{"keyboard-tr", "土耳其", "Turkish"},
	{"keyboard-tr-f", "土耳其", "Turkish"},
	{"keyboard-tr-crh", "土耳其", "Turkish"},
	{"keyboard-tr-crh_f", "土耳其", "Turkish"},
	{"keyboard-tr-sun_type6", "土耳其", "Turkish"},
	{"keyboard-th-pat", "泰语", "Thai"},
	{"keyboard-th-tis", "泰语", "Thai"},
	{"keyboard-th", "泰语", "Thai"},
	{"keyboard-tw-indigenous", "台湾", "Taiwan"},
	{"keyboard-tw", "台湾", "Taiwan"},
	{"keyboard-tw-saisiyat", "台湾", "Taiwan"},
	{"keyboard-tj-legacy", "塔吉克", "Tajik"},
	{"keyboard-tj", "塔吉克", "Tajik"},
	{"keyboard-tz", "斯瓦希里语", "Swahili"},
	{"keyboard-ke", "斯瓦希里语", "Swahili"},
	{"keyboard-ke-kik", "斯瓦希里语", "Swahili"},
	{"keyboard-si", "斯洛文尼亚语", "Slovenian"},
	{"keyboard-si-alternatequotes", "斯洛文尼亚语", "Slovenian"},
	{"keyboard-si-us", "斯洛文尼亚语", "Slovenian"},
	{"keyboard-sk", "斯洛伐克语", "Slovak"},
	{"keyboard-sk-sun_type6", "斯洛伐克语", "Slovak"},
	{"keyboard-sk-bksl", "斯洛伐克语", "Slovak"},
	{"keyboard-sk-qwerty_bksl", "斯洛伐克语", "Slovak"},
	{"keyboard-sk-qwerty", "斯洛伐克语", "Slovak"},
	{"keyboard-epo", "世界语", "Esperanto"},
	{"keyboard-epo-legacy", "世界语", "Esperanto"},
	{"keyboard-lk", "僧伽罗语", "Sinhala"},
	{"keyboard-lk-us", "僧伽罗语", "Sinhala"},
	{"keyboard-lk-tam_TAB", "僧伽罗语", "Sinhala"},
	{"keyboard-lk-tam_unicode", "僧伽罗语", "Sinhala"},
	{"keyboard-rs", "塞尔维亚语", "Serbian"},
	{"keyboard-rs-latinyz", "塞尔维亚语", "Serbian"},
	{"keyboard-rs-yz", "塞尔维亚语", "Serbian"},
	{"keyboard-rs-latinalternatequotes", "塞尔维亚语", "Serbian"},
	{"keyboard-rs-latin", "塞尔维亚语", "Serbian"},
	{"keyboard-rs-combiningkeys", "塞尔维亚语", "Serbian"},
	{"keyboard-rs-latinunicodeyz", "塞尔维亚语", "Serbian"},
	{"keyboard-rs-latinunicode", "塞尔维亚语", "Serbian"},
	{"keyboard-rs-rue", "塞尔维亚语", "Serbian"},
	{"keyboard-rs-alternatequotes", "塞尔维亚语", "Serbian"},
	{"keyboard-se-ovd", "瑞典语", "Swedish"},
	{"keyboard-se-us", "瑞典语", "Swedish"},
	{"keyboard-se-mac", "瑞典语", "Swedish"},
	{"keyboard-se-dvorak", "瑞典语", "Swedish"},
	{"keyboard-se-nodeadkeys", "瑞典语", "Swedish"},
	{"keyboard-se", "瑞典语", "Swedish"},
	{"keyboard-se-dvorak_a5", "瑞典语", "Swedish"},
	{"keyboard-se-smi", "瑞典语", "Swedish"},
	{"keyboard-se-swl", "瑞典语", "Swedish"},
	{"keyboard-se-sun_type6", "瑞典语", "Swedish"},
	{"keyboard-se-rus", "瑞典语", "Swedish"},
	{"keyboard-se-rus_nodeadkeys", "瑞典语", "Swedish"},
	{"keyboard-se-us_dvorak", "瑞典语", "Swedish"},
	{"keyboard-se-svdvorak", "瑞典语", "Swedish"},
	{"keyboard-nec_vndr/jp", "日语", "Japanese"},
	{"keyboard-jp", "日语", "Japanese"},
	{"keyboard-jp-sun_type7", "日语", "Japanese"},
	{"keyboard-jp-mac", "日语", "Japanese"},
	{"keyboard-jp-OADG109A", "日语", "Japanese"},
	{"keyboard-jp-kana", "日语", "Japanese"},
	{"keyboard-jp-dvorak", "日语", "Japanese"},
	{"keyboard-jp-sun_type6", "日语", "Japanese"},
	{"keyboard-jp-kana86", "日语", "Japanese"},
	{"keyboard-jp-sun_type7_suncompat", "日语", "Japanese"},
	{"keyboard-pt", "葡萄牙", "Portuguese"},
	{"keyboard-pt-mac", "葡萄牙", "Portuguese"},
	{"keyboard-pt-nativo-epo", "葡萄牙", "Portuguese"},
	{"keyboard-pt-sundeadkeys", "葡萄牙", "Portuguese"},
	{"keyboard-pt-mac_sundeadkeys", "葡萄牙", "Portuguese"},
	{"keyboard-pt-nativo", "葡萄牙", "Portuguese"},
	{"keyboard-pt-colemak", "葡萄牙", "Portuguese"},
	{"keyboard-pt-sun_type6", "葡萄牙", "Portuguese"},
	{"keyboard-pt-nativo-us", "葡萄牙", "Portuguese"},
	{"keyboard-pt-nodeadkeys", "葡萄牙", "Portuguese"},
	{"keyboard-pt-mac_nodeadkeys", "葡萄牙", "Portuguese"},
	{"keyboard-br", "葡萄牙", "Portuguese"},
	{"keyboard-br-thinkpad", "葡萄牙", "Portuguese"},
	{"keyboard-br-sun_type6", "葡萄牙", "Portuguese"},
	{"keyboard-br-nativo-us", "葡萄牙", "Portuguese"},
	{"keyboard-br-nativo-epo", "葡萄牙", "Portuguese"},
	{"keyboard-br-dvorak", "葡萄牙", "Portuguese"},
	{"keyboard-br-nativo", "葡萄牙", "Portuguese"},
	{"keyboard-br-nodeadkeys", "葡萄牙", "Portuguese"},
	{"keyboard-no", "挪威语", "Norwegian"},
	{"keyboard-no-smi", "挪威语", "Norwegian"},
	{"keyboard-no-dvorak", "挪威语", "Norwegian"},
	{"keyboard-no-smi_nodeadkeys", "挪威语", "Norwegian"},
	{"keyboard-no-winkeys", "挪威语", "Norwegian"},
	{"keyboard-no-sun_type6", "挪威语", "Norwegian"},
	{"keyboard-no-nodeadkeys", "挪威语", "Norwegian"},
	{"keyboard-no-mac", "挪威语", "Norwegian"},
	{"keyboard-no-mac_nodeadkeys", "挪威语", "Norwegian"},
	{"keyboard-no-colemak", "挪威语", "Norwegian"},
	{"keyboard-np", "尼泊尔语", "Nepali"},
	{"keyboard-md", "摩尔多瓦语", "Moldavian"},
	{"keyboard-md-gag", "摩尔多瓦语", "Moldavian"},
	{"keyboard-mm", "缅甸", "Burmese"},
	{"keyboard-mm-zawgyi", "缅甸", "Burmese"},
	{"keyboard-bd", "孟加拉语", "Bangla"},
	{"keyboard-bd-probhat", "孟加拉语", "Bangla"},
	{"keyboard-mn", "蒙古", "Mongolian"},
	{"keyboard-mao", "毛利语", "Maori"},
	{"keyboard-brai", "盲文", "Braille"},
	{"keyboard-brai-left_hand", "盲文", "Braille"},
	{"keyboard-brai-left_hand_invert", "盲文", "Braille"},
	{"keyboard-brai-right_hand", "盲文", "Braille"},
	{"keyboard-brai-right_hand_invert", "盲文", "Braille"},
	{"keyboard-mk", "马其顿语", "Macedonian"},
	{"keyboard-mk-nodeadkeys", "马其顿语", "Macedonian"},
	{"keyboard-my", "马来语", "Malay"},
	{"keyboard-my-phonetic", "马来语", "Malay"},
	{"keyboard-mt", "马耳他语", "Maltese"},
	{"keyboard-mt-us", "马耳他语", "Maltese"},
	{"keyboard-ro", "罗马尼亚语", "Romanian"},
	{"keyboard-ro-sun_type6", "罗马尼亚语", "Romanian"},
	{"keyboard-ro-cedilla", "罗马尼亚语", "Romanian"},
	{"keyboard-ro-std_cedilla", "罗马尼亚语", "Romanian"},
	{"keyboard-ro-crh_dobruja", "罗马尼亚语", "Romanian"},
	{"keyboard-ro-winkeys", "罗马尼亚语", "Romanian"},
	{"keyboard-ro-std", "罗马尼亚语", "Romanian"},
	{"keyboard-ro-ergonomic", "罗马尼亚语", "Romanian"},
	{"keyboard-lt", "立陶宛语", "Lithuanian"},
	{"keyboard-lt-ibm", "立陶宛语", "Lithuanian"},
	{"keyboard-lt-us_dvorak", "立陶宛语", "Lithuanian"},
	{"keyboard-lt-lekp", "立陶宛语", "Lithuanian"},
	{"keyboard-lt-us", "立陶宛语", "Lithuanian"},
	{"keyboard-lt-std", "立陶宛语", "Lithuanian"},
	{"keyboard-lt-lekpa", "立陶宛语", "Lithuanian"},
	{"keyboard-lt-sun_type6", "立陶宛语", "Lithuanian"},
	{"keyboard-la", "老挝语", "Lao"},
	{"keyboard-la-stea", "老挝语", "Lao"},
	{"keyboard-lv", "拉脱维亚", "Latvian"},
	{"keyboard-lv-sun_type6", "拉脱维亚", "Latvian"},
	{"keyboard-lv-apostrophecolemak", "拉脱维亚", "Latvian"},
	{"keyboard-lv-colemak", "拉脱维亚", "Latvian"},
	{"keyboard-lv-ykeydvorakprogr", "拉脱维亚", "Latvian"},
	{"keyboard-lv-dvorakprogr", "拉脱维亚", "Latvian"},
	{"keyboard-lv-minuskeydvorak", "拉脱维亚", "Latvian"},
	{"keyboard-lv-ykeydvorak", "拉脱维亚", "Latvian"},
	{"keyboard-lv-adapted", "拉脱维亚", "Latvian"},
	{"keyboard-lv-ergonomic", "拉脱维亚", "Latvian"},
	{"keyboard-lv-tilde", "拉脱维亚", "Latvian"},
	{"keyboard-lv-apostrophe", "拉脱维亚", "Latvian"},
	{"keyboard-lv-dvorak", "拉脱维亚", "Latvian"},
	{"keyboard-lv-minuskeydvorakprogr", "拉脱维亚", "Latvian"},
	{"keyboard-lv-fkey", "拉脱维亚", "Latvian"},
	{"keyboard-lv-modern", "拉脱维亚", "Latvian"},
	{"keyboard-hr", "克罗地亚", "Croatian"},
	{"keyboard-hr-us", "克罗地亚", "Croatian"},
	{"keyboard-hr-unicode", "克罗地亚", "Croatian"},
	{"keyboard-hr-unicodeus", "克罗地亚", "Croatian"},
	{"keyboard-hr-alternatequotes", "克罗地亚", "Croatian"},
	{"keyboard-kg", "柯尔克孜语", "Kirgiz"},
	{"keyboard-kg-phonetic", "柯尔克孜语", "Kirgiz"},
	{"keyboard-cz", "捷克", "Czech"},
	{"keyboard-cz-qwerty_bksl", "捷克", "Czech"},
	{"keyboard-cz-qwerty", "捷克", "Czech"},
	{"keyboard-cz-bksl", "捷克", "Czech"},
	{"keyboard-cz-dvorak-ucw", "捷克", "Czech"},
	{"keyboard-cz-ucw", "捷克", "Czech"},
	{"keyboard-cz-rus", "捷克", "Czech"},
	{"keyboard-cz-sun_type6", "捷克", "Czech"},
	{"db", "简体中文 (中国)", "Chinese"},
	{"shuangpin", "简体中文 (中国)", "Chinese"},
	{"qxm", "简体中文 (中国)", "Chinese"},
	{"cangjie", "简体中文 (中国)", "Chinese"},
	{"wbx", "简体中文 (中国)", "Chinese"},
	{"wanfeng", "简体中文 (中国)", "Chinese"},
	{"erbi", "简体中文 (中国)", "Chinese"},
	{"zrm", "简体中文 (中国)", "Chinese"},
	{"pinyin", "简体中文 (中国)", "Chinese"},
	{"wbpy", "简体中文 (中国)", "Chinese"},
	{"keyboard-me", "黑山语", "Montenegrin"},
	{"keyboard-me-cyrillicalternatequotes", "黑山语", "Montenegrin"},
	{"keyboard-me-cyrillicyz", "黑山语", "Montenegrin"},
	{"keyboard-me-cyrillic", "黑山语", "Montenegrin"},
	{"keyboard-me-latinyz", "黑山语", "Montenegrin"},
	{"keyboard-me-latinunicode", "黑山语", "Montenegrin"},
	{"keyboard-me-latinunicodeyz", "黑山语", "Montenegrin"},
	{"keyboard-me-latinalternatequotes", "黑山语", "Montenegrin"},
	{"keyboard-nl", "荷兰语", "Dutch"},
	{"keyboard-nl-sun_type6", "荷兰语", "Dutch"},
	{"keyboard-nl-sundeadkeys", "荷兰语", "Dutch"},
	{"keyboard-nl-mac", "荷兰语", "Dutch"},
	{"keyboard-nl-std", "荷兰语", "Dutch"},
	{"keyboard-cn", "汉语", "Chinese"},
	{"keyboard-cn-altgr-pinyin", "汉语", "Chinese"},
	{"keyboard-cn-tib_asciinum", "汉语", "Chinese"},
	{"keyboard-cn-tib", "汉语", "Chinese"},
	{"keyboard-cn-ug", "汉语", "Chinese"},
	{"keyboard-kz", "哈萨克语", "Kazakh"},
	{"keyboard-kz-latin", "哈萨克语", "Kazakh"},
	{"keyboard-kz-ruskaz", "哈萨克语", "Kazakh"},
	{"keyboard-kz-kazrus", "哈萨克语", "Kazakh"},
	{"keyboard-kz-ext", "哈萨克语", "Kazakh"},
	{"keyboard-trans", "国际音标", "International Phonetic Alphabet"},
	{"keyboard-ge", "格鲁吉亚语", "Georgian"},
	{"keyboard-ge-ergonomic", "格鲁吉亚语", "Georgian"},
	{"keyboard-ge-mess", "格鲁吉亚语", "Georgian"},
	{"keyboard-ge-os", "格鲁吉亚语", "Georgian"},
	{"keyboard-ge-ru", "格鲁吉亚语", "Georgian"},
	{"keyboard-kh", "高棉语", "Khmer"},
	{"keyboard-fi", "芬兰语", "Finnish"},
	{"keyboard-fi-fidvorak", "芬兰语", "Finnish"},
	{"keyboard-fi-sun_type6", "芬兰语", "Finnish"},
	{"keyboard-fi-mac", "芬兰语", "Finnish"},
	{"keyboard-fi-nodeadkeys", "芬兰语", "Finnish"},
	{"keyboard-fi-smi", "芬兰语", "Finnish"},
	{"keyboard-fi-classic", "芬兰语", "Finnish"},
	{"keyboard-fi-winkeys", "芬兰语", "Finnish"},
	{"keyboard-fi-das", "芬兰语", "Finnish"},
	{"keyboard-ph", "菲律宾语", "Filipino"},
	{"keyboard-ph-colemak-bay", "菲律宾语", "Filipino"},
	{"keyboard-ph-dvorak-bay", "菲律宾语", "Filipino"},
	{"keyboard-ph-capewell-qwerf2k6-bay", "菲律宾语", "Filipino"},
	{"keyboard-ph-capewell-dvorak-bay", "菲律宾语", "Filipino"},
	{"keyboard-ph-capewell-qwerf2k6", "菲律宾语", "Filipino"},
	{"keyboard-ph-dvorak", "菲律宾语", "Filipino"},
	{"keyboard-ph-qwerty-bay", "菲律宾语", "Filipino"},
	{"keyboard-ph-colemak", "菲律宾语", "Filipino"},
	{"keyboard-ph-capewell-dvorak", "菲律宾语", "Filipino"},
	{"keyboard-ca", "法语", "French"},
	{"keyboard-ca-sun_type6", "法语", "French"},
	{"keyboard-ca-shs", "法语", "French"},
	{"keyboard-ca-kut", "法语", "French"},
	{"keyboard-ca-ike", "法语", "French"},
	{"keyboard-ca-multi", "法语", "French"},
	{"keyboard-ca-multix", "法语", "French"},
	{"keyboard-ca-fr-legacy", "法语", "French"},
	{"keyboard-ca-fr-dvorak", "法语", "French"},
	{"keyboard-ca-eng", "法语", "French"},
	{"keyboard-ca-multi-2gr", "法语", "French"},
	{"keyboard-gn", "法语", "French"},
	{"keyboard-cd", "法语", "French"},
	{"keyboard-fr", "法语", "French"},
	{"keyboard-fr-oss_sundeadkeys", "法语", "French"},
	{"keyboard-fr-latin9", "法语", "French"},
	{"keyboard-fr-latin9_sundeadkeys", "法语", "French"},
	{"keyboard-fr-sundeadkeys", "法语", "French"},
	{"keyboard-fr-sun_type6", "法语", "French"},
	{"keyboard-fr-nodeadkeys", "法语", "French"},
	{"keyboard-fr-oci", "法语", "French"},
	{"keyboard-fr-us-azerty", "法语", "French"},
	{"keyboard-fr-oss_nodeadkeys", "法语", "French"},
	{"keyboard-fr-oss", "法语", "French"},
	{"keyboard-fr-bepo", "法语", "French"},
	{"keyboard-fr-latin9_nodeadkeys", "法语", "French"},
	{"keyboard-fr-bepo_latin9", "法语", "French"},
	{"keyboard-fr-dvorak", "法语", "French"},
	{"keyboard-fr-mac", "法语", "French"},
	{"keyboard-fr-azerty", "法语", "French"},
	{"keyboard-fr-geo", "法语", "French"},
	{"keyboard-fr-bre", "法语", "French"},
	{"keyboard-fr-oss_latin9", "法语", "French"},
	{"keyboard-fr-us", "法语", "French"},
	{"keyboard-fr-us-alt", "法语", "French"},
	{"keyboard-tg", "法语", "French"},
	{"keyboard-fo", "法罗", "Faroese"},
	{"keyboard-fo-nodeadkeys", "法罗", "Faroese"},
	{"keyboard-ru", "俄语", "Russian"},
	{"keyboard-ru-prxn", "俄语", "Russian"},
	{"keyboard-ru-unipunct", "俄语", "Russian"},
	{"keyboard-ru-ruu", "俄语", "Russian"},
	{"keyboard-ru-chu", "俄语", "Russian"},
	{"keyboard-ru-phonetic_dvorak", "俄语", "Russian"},
	{"keyboard-ru-xal", "俄语", "Russian"},
	{"keyboard-ru-cv_latin", "俄语", "Russian"},
	{"keyboard-ru-cv", "俄语", "Russian"},
	{"keyboard-ru-os_winkeys", "俄语", "Russian"},
	{"keyboard-ru-legacy", "俄语", "Russian"},
	{"keyboard-ru-phonetic_winkeys", "俄语", "Russian"},
	{"keyboard-ru-phonetic", "俄语", "Russian"},
	{"keyboard-ru-bak", "俄语", "Russian"},
	{"keyboard-ru-phonetic_azerty", "俄语", "Russian"},
	{"keyboard-ru-sah", "俄语", "Russian"},
	{"keyboard-ru-kom", "俄语", "Russian"},
	{"keyboard-ru-srp", "俄语", "Russian"},
	{"keyboard-ru-dos", "俄语", "Russian"},
	{"keyboard-ru-typewriter-legacy", "俄语", "Russian"},
	{"keyboard-ru-tt", "俄语", "Russian"},
	{"keyboard-ru-typewriter", "俄语", "Russian"},
	{"keyboard-ru-mac", "俄语", "Russian"},
	{"keyboard-ru-os_legacy", "俄语", "Russian"},
	{"keyboard-ru-phonetic_yazherty", "俄语", "Russian"},
	{"keyboard-ru-chm", "俄语", "Russian"},
	{"keyboard-ru-sun_type6", "俄语", "Russian"},
	{"keyboard-ru-udm", "俄语", "Russian"},
	{"keyboard-ru-rulemak", "俄语", "Russian"},
	{"keyboard-ru-phonetic_fr", "俄语", "Russian"},
	{"keyboard-mv", "迪维希语", "Dhivehi"},
	{"keyboard-ch", "德语", "German"},
	{"keyboard-ch-sun_type6_de", "德语", "German"},
	{"keyboard-ch-fr_sundeadkeys", "德语", "German"},
	{"keyboard-ch-fr_nodeadkeys", "德语", "German"},
	{"keyboard-ch-de_nodeadkeys", "德语", "German"},
	{"keyboard-ch-legacy", "德语", "German"},
	{"keyboard-ch-de_mac", "德语", "German"},
	{"keyboard-ch-fr_mac", "德语", "German"},
	{"keyboard-ch-sun_type6_fr", "德语", "German"},
	{"keyboard-ch-fr", "德语", "German"},
	{"keyboard-ch-de_sundeadkeys", "德语", "German"},
	{"keyboard-at", "德语", "German"},
	{"keyboard-at-mac", "德语", "German"},
	{"keyboard-at-sundeadkeys", "德语", "German"},
	{"keyboard-at-nodeadkeys", "德语", "German"},
	{"keyboard-de", "德语", "German"},
	{"keyboard-de-ru-recom", "德语", "German"},
	{"keyboard-de-neo_qwerty", "德语", "German"},
	{"keyboard-de-bone", "德语", "German"},
	{"keyboard-de-koy", "德语", "German"},
	{"keyboard-de-adnw", "德语", "German"},
	{"keyboard-de-sun_type6", "德语", "German"},
	{"keyboard-de-pl", "德语", "German"},
	{"keyboard-de-hu", "德语", "German"},
	{"keyboard-de-us", "德语", "German"},
	{"keyboard-de-deadtilde", "德语", "German"},
	{"keyboard-de-qwerty", "德语", "German"},
	{"keyboard-de-dsb_qwertz", "德语", "German"},
	{"keyboard-de-dsb", "德语", "German"},
	{"keyboard-de-mac_nodeadkeys", "德语", "German"},
	{"keyboard-de-mac", "德语", "German"},
	{"keyboard-de-ro_nodeadkeys", "德语", "German"},
	{"keyboard-de-T3", "德语", "German"},
	{"keyboard-de-deadgraveacute", "德语", "German"},
	{"keyboard-de-ru-translit", "德语", "German"},
	{"keyboard-de-dvorak", "德语", "German"},
	{"keyboard-de-neo", "德语", "German"},
	{"keyboard-de-deadacute", "德语", "German"},
	{"keyboard-de-nodeadkeys", "德语", "German"},
	{"keyboard-de-bone_eszett_home", "德语", "German"},
	{"keyboard-de-sundeadkeys", "德语", "German"},
	{"keyboard-de-ru", "德语", "German"},
	{"keyboard-de-ro", "德语", "German"},
	{"keyboard-de-lld", "德语", "German"},
	{"keyboard-de-tr", "德语", "German"},
	{"keyboard-de-neo_qwertz", "德语", "German"},
	{"keyboard-dk", "丹麦语", "Danish"},
	{"keyboard-dk-sun_type6", "丹麦语", "Danish"},
	{"keyboard-dk-dvorak", "丹麦语", "Danish"},
	{"keyboard-dk-nodeadkeys", "丹麦语", "Danish"},
	{"keyboard-dk-winkeys", "丹麦语", "Danish"},
	{"keyboard-dk-mac", "丹麦语", "Danish"},
	{"keyboard-dk-mac_nodeadkeys", "丹麦语", "Danish"},
	{"keyboard-bw", "茨瓦纳语", "Tswana"},
	{"keyboard-kr", "朝鲜语", "Korean"},
	{"keyboard-kr-sun_type6", "朝鲜语", "Korean"},
	{"keyboard-kr-kr104", "朝鲜语", "Korean"},
	{"keyboard-bt", "不丹语", "Dzongkha"},
	{"keyboard-ir", "波斯语", "Persian"},
	{"keyboard-ir-ku_ara", "波斯语", "Persian"},
	{"keyboard-ir-ku_alt", "波斯语", "Persian"},
	{"keyboard-ir-pes_keypad", "波斯语", "Persian"},
	{"keyboard-ir-ave", "波斯语", "Persian"},
	{"keyboard-ir-ku", "波斯语", "Persian"},
	{"keyboard-ir-ku_f", "波斯语", "Persian"},
	{"keyboard-ba", "波斯尼亚语", "Bosnian"},
	{"keyboard-ba-unicode", "波斯尼亚语", "Bosnian"},
	{"keyboard-ba-alternatequotes", "波斯尼亚语", "Bosnian"},
	{"keyboard-ba-unicodeus", "波斯尼亚语", "Bosnian"},
	{"keyboard-ba-us", "波斯尼亚语", "Bosnian"},
	{"keyboard-pl", "波兰语", "Polish"},
	{"keyboard-pl-glagolica", "波兰语", "Polish"},
	{"keyboard-pl-colemak", "波兰语", "Polish"},
	{"keyboard-pl-dvp", "波兰语", "Polish"},
	{"keyboard-pl-ru_phonetic_dvorak", "波兰语", "Polish"},
	{"keyboard-pl-szl", "波兰语", "Polish"},
	{"keyboard-pl-dvorak_altquotes", "波兰语", "Polish"},
	{"keyboard-pl-intl", "波兰语", "Polish"},
	{"keyboard-pl-dvorak", "波兰语", "Polish"},
	{"keyboard-pl-sun_type6", "波兰语", "Polish"},
	{"keyboard-pl-legacy", "波兰语", "Polish"},
	{"keyboard-pl-csb", "波兰语", "Polish"},
	{"keyboard-pl-qwertz", "波兰语", "Polish"},
	{"keyboard-pl-dvorak_quotes", "波兰语", "Polish"},
	{"keyboard-is", "冰岛", "Icelandic"},
	{"keyboard-is-dvorak", "冰岛", "Icelandic"},
	{"keyboard-is-mac", "冰岛", "Icelandic"},
	{"keyboard-is-mac_legacy", "冰岛", "Icelandic"},
	{"keyboard-is-Sundeadkeys", "冰岛", "Icelandic"},
	{"keyboard-is-nodeadkeys", "冰岛", "Icelandic"},
	{"keyboard-be", "比利时语", "Belgian"},
	{"keyboard-be-iso-alternate", "比利时语", "Belgian"},
	{"keyboard-be-nodeadkeys", "比利时语", "Belgian"},
	{"keyboard-be-sundeadkeys", "比利时语", "Belgian"},
	{"keyboard-be-oss_latin9", "比利时语", "Belgian"},
	{"keyboard-be-oss", "比利时语", "Belgian"},
	{"keyboard-be-oss_sundeadkeys", "比利时语", "Belgian"},
	{"keyboard-be-wang", "比利时语", "Belgian"},
	{"keyboard-be-sun_type6", "比利时语", "Belgian"},
	{"keyboard-bg", "保加利亚", "Bulgaria"},
	{"keyboard-bg-phonetic", "保加利亚", "Bulgaria"},
	{"keyboard-bg-bas_phonetic", "保加利亚", "Bulgaria"},
	{"keyboard-ml", "班巴拉语", "Bambara"},
	{"keyboard-ml-us-intl", "班巴拉语", "Bambara"},
	{"keyboard-ml-fr-oss", "班巴拉语", "Bambara"},
	{"keyboard-ml-us-mac", "班巴拉语", "Bambara"},
	{"keyboard-dz", "柏柏尔语", "Berber"},
	{"keyboard-dz-ar", "柏柏尔语", "Berber"},
	{"keyboard-dz-ber", "柏柏尔语", "Berber"},
	{"keyboard-by", "白俄罗斯语", "Belarusian"},
	{"keyboard-by-legacy", "白俄罗斯语", "Belarusian"},
	{"keyboard-by-latin", "白俄罗斯语", "Belarusian"},
	{"keyboard-ee", "爱沙尼亚", "Estonia"},
	{"keyboard-ee-us", "爱沙尼亚", "Estonia"},
	{"keyboard-ee-dvorak", "爱沙尼亚", "Estonia"},
	{"keyboard-ee-nodeadkeys", "爱沙尼亚", "Estonia"},
	{"keyboard-ee-sun_type6", "爱沙尼亚", "Estonia"},
	{"keyboard-ie", "爱尔兰", "Irish"},
	{"keyboard-ie-ogam_is434", "爱尔兰", "Irish"},
	{"keyboard-ie-ogam", "爱尔兰", "Irish"},
	{"keyboard-ie-CloGaelach", "爱尔兰", "Irish"},
	{"keyboard-ie-UnicodeExpert", "爱尔兰", "Irish"},
	{"keyboard-az", "阿塞拜疆语", "Azerbaijani"},
	{"keyboard-az-cyrillic", "阿塞拜疆语", "Azerbaijani"},
	{"keyboard-et", "阿姆哈拉语", "Amharic"},
	{"keyboard-sy", "阿拉伯语", "Arabic"},
	{"keyboard-sy-ku", "阿拉伯语", "Arabic"},
	{"keyboard-sy-syc", "阿拉伯语", "Arabic"},
	{"keyboard-sy-ku_alt", "阿拉伯语", "Arabic"},
	{"keyboard-sy-ku_f", "阿拉伯语", "Arabic"},
	{"keyboard-sy-syc_phonetic", "阿拉伯语", "Arabic"},
	{"keyboard-ma", "阿拉伯语", "Arabic"},
	{"keyboard-ma-tifinagh-extended-phonetic", "阿拉伯语", "Arabic"},
	{"keyboard-ma-tifinagh-extended", "阿拉伯语", "Arabic"},
	{"keyboard-ma-tifinagh", "阿拉伯语", "Arabic"},
	{"keyboard-ma-french", "阿拉伯语", "Arabic"},
	{"keyboard-ma-tifinagh-alt-phonetic", "阿拉伯语", "Arabic"},
	{"keyboard-ma-tifinagh-alt", "阿拉伯语", "Arabic"},
	{"keyboard-ma-tifinagh-phonetic", "阿拉伯语", "Arabic"},
	{"keyboard-ara", "阿拉伯语", "Arabic"},
	{"keyboard-ara-qwerty_digits", "阿拉伯语", "Arabic"},
	{"keyboard-ara-qwerty", "阿拉伯语", "Arabic"},
	{"keyboard-ara-olpc", "阿拉伯语", "Arabic"},
	{"keyboard-ara-azerty", "阿拉伯语", "Arabic"},
	{"keyboard-ara-buckwalter", "阿拉伯语", "Arabic"},
	{"keyboard-ara-mac", "阿拉伯语", "Arabic"},
	{"keyboard-ara-uga", "阿拉伯语", "Arabic"},
	{"keyboard-ara-basic_ext_digits", "阿拉伯语", "Arabic"},
	{"keyboard-ara-digits", "阿拉伯语", "Arabic"},
	{"keyboard-ara-sun_type6", "阿拉伯语", "Arabic"},
	{"keyboard-ara-azerty_digits", "阿拉伯语", "Arabic"},
	{"keyboard-ara-basic_ext", "阿拉伯语", "Arabic"},
	{"keyboard-af", "阿富汗", "Afghanistan"},
	{"keyboard-af-ps", "阿富汗", "Afghanistan"},
	{"keyboard-af-fa-olpc", "阿富汗", "Afghanistan"},
	{"keyboard-af-uz", "阿富汗", "Afghanistan"},
	{"keyboard-af-olpc-ps", "阿富汗", "Afghanistan"},
	{"keyboard-af-uz-olpc", "阿富汗", "Afghanistan"},
	{"keyboard-al", "阿尔巴尼亚", "Albanian"},
	{"keyboard-al-plisi", "阿尔巴尼亚", "Albanian"},
	{"keyboard-eu", "EurKEY", "EurKEY"},
	{"keyboard-apl", "APL", "APL"},
	{"keyboard-apl-aplx", "APL", "APL"},
	{"keyboard-apl-dyalog", "APL", "APL"},
	{"keyboard-apl-unified", "APL", "APL"},
	{"keyboard-apl-apl2", "APL", "APL"},
	{"keyboard-apl-sax", "APL", "APL"},
	{"keyboard-apl-aplplusII", "APL", "APL"},

};

int initCategroyLanguageMap()
{
    int count = sizeof(languageList) / sizeof(s_languageList);
    int index = 0;

    g_uniqueNameToEnglishMap.clear();
    g_uniqueNameToChineseMap.clear();
    for (index = 0; index < count; index++) {
        g_uniqueNameToEnglishMap[languageList[index].uniqueName] = languageList[index].englishName;
        g_uniqueNameToChineseMap[languageList[index].uniqueName] = languageList[index].chineseName;
    }

    return 0;
}

QString getEnglishLanguageName(QString uniqueName)
{
    QString englishName = "";

    if (g_uniqueNameToEnglishMap.contains(uniqueName)) {
        englishName = g_uniqueNameToEnglishMap[uniqueName];
    }
    else {
        englishName = "unknown";
    }

    return englishName;
}

QString getChineseLanguageName(QString uniqueName)
{
    QString chineseName = "";

    if (g_uniqueNameToChineseMap.contains(uniqueName)) {
        chineseName = g_uniqueNameToChineseMap[uniqueName];
    }
    else {
        chineseName = "unknown";

    }
    return chineseName;
}

void setUseIMList(const FcitxQtStringKeyValueList& useIMs)
{
    g_useIMList = useIMs;
}

FcitxQtStringKeyValueList& getUseIMList()
{
    return g_useIMList;
}

void setMaxUseIMLanguageIndex(int index)
{
    if (index > g_maxLanguageIndex) {
        g_maxLanguageIndex = index;
    }
}

int getMaxUseIMLanguageIndex()
{
    return g_maxLanguageIndex;
}

void setCurrentIMViewIndex(int index)
{
    g_currentIMViewIndex = index;
}

int getCurrentIMViewIndex()
{
    return g_currentIMViewIndex;
}
