(function (global, factory) {
	typeof exports === 'object' && typeof module !== 'undefined' ? module.exports = factory() :
	typeof define === 'function' && define.amd ? define(factory) :
	(global = global || self, global.anchorme = factory());
}(this, (function () { 'use strict';

	var commonjsGlobal = typeof globalThis !== 'undefined' ? globalThis : typeof window !== 'undefined' ? window : typeof global !== 'undefined' ? global : typeof self !== 'undefined' ? self : {};

	function unwrapExports (x) {
		return x && x.__esModule && Object.prototype.hasOwnProperty.call(x, 'default') ? x['default'] : x;
	}

	function createCommonjsModule(fn, module) {
		return module = { exports: {} }, fn(module, module.exports), module.exports;
	}

	var tlds = createCommonjsModule(function (module, exports) {
	Object.defineProperty(exports, "__esModule", { value: true });
	exports.TLDs = "(AAA|AARP|ABARTH|ABB|ABBOTT|ABBVIE|ABC|ABLE|ABOGADO|ABUDHABI|AC|ACADEMY|ACCENTURE|ACCOUNTANT|ACCOUNTANTS|ACO|ACTOR|AD|ADAC|ADS|ADULT|AE|AEG|AERO|AETNA|AF|AFAMILYCOMPANY|AFL|AFRICA|AG|AGAKHAN|AGENCY|AI|AIG|AIGO|AIRBUS|AIRFORCE|AIRTEL|AKDN|AL|ALFAROMEO|ALIBABA|ALIPAY|ALLFINANZ|ALLSTATE|ALLY|ALSACE|ALSTOM|AM|AMERICANEXPRESS|AMERICANFAMILY|AMEX|AMFAM|AMICA|AMSTERDAM|ANALYTICS|ANDROID|ANQUAN|ANZ|AO|AOL|APARTMENTS|APP|APPLE|AQ|AQUARELLE|AR|ARAB|ARAMCO|ARCHI|ARMY|ARPA|ART|ARTE|AS|ASDA|ASIA|ASSOCIATES|AT|ATHLETA|ATTORNEY|AU|AUCTION|AUDI|AUDIBLE|AUDIO|AUSPOST|AUTHOR|AUTO|AUTOS|AVIANCA|AW|AWS|AX|AXA|AZ|AZURE|BA|BABY|BAIDU|BANAMEX|BANANAREPUBLIC|BAND|BANK|BAR|BARCELONA|BARCLAYCARD|BARCLAYS|BAREFOOT|BARGAINS|BASEBALL|BASKETBALL|BAUHAUS|BAYERN|BB|BBC|BBT|BBVA|BCG|BCN|BD|BE|BEATS|BEAUTY|BEER|BENTLEY|BERLIN|BEST|BESTBUY|BET|BF|BG|BH|BHARTI|BI|BIBLE|BID|BIKE|BING|BINGO|BIO|BIZ|BJ|BLACK|BLACKFRIDAY|BLOCKBUSTER|BLOG|BLOOMBERG|BLUE|BM|BMS|BMW|BN|BNPPARIBAS|BO|BOATS|BOEHRINGER|BOFA|BOM|BOND|BOO|BOOK|BOOKING|BOSCH|BOSTIK|BOSTON|BOT|BOUTIQUE|BOX|BR|BRADESCO|BRIDGESTONE|BROADWAY|BROKER|BROTHER|BRUSSELS|BS|BT|BUDAPEST|BUGATTI|BUILD|BUILDERS|BUSINESS|BUY|BUZZ|BV|BW|BY|BZ|BZH|CA|CAB|CAFE|CAL|CALL|CALVINKLEIN|CAM|CAMERA|CAMP|CANCERRESEARCH|CANON|CAPETOWN|CAPITAL|CAPITALONE|CAR|CARAVAN|CARDS|CARE|CAREER|CAREERS|CARS|CASA|CASE|CASEIH|CASH|CASINO|CAT|CATERING|CATHOLIC|CBA|CBN|CBRE|CBS|CC|CD|CEB|CENTER|CEO|CERN|CF|CFA|CFD|CG|CH|CHANEL|CHANNEL|CHARITY|CHASE|CHAT|CHEAP|CHINTAI|CHRISTMAS|CHROME|CHURCH|CI|CIPRIANI|CIRCLE|CISCO|CITADEL|CITI|CITIC|CITY|CITYEATS|CK|CL|CLAIMS|CLEANING|CLICK|CLINIC|CLINIQUE|CLOTHING|CLOUD|CLUB|CLUBMED|CM|CN|CO|COACH|CODES|COFFEE|COLLEGE|COLOGNE|COM|COMCAST|COMMBANK|COMMUNITY|COMPANY|COMPARE|COMPUTER|COMSEC|CONDOS|CONSTRUCTION|CONSULTING|CONTACT|CONTRACTORS|COOKING|COOKINGCHANNEL|COOL|COOP|CORSICA|COUNTRY|COUPON|COUPONS|COURSES|CPA|CR|CREDIT|CREDITCARD|CREDITUNION|CRICKET|CROWN|CRS|CRUISE|CRUISES|CSC|CU|CUISINELLA|CV|CW|CX|CY|CYMRU|CYOU|CZ|DABUR|DAD|DANCE|DATA|DATE|DATING|DATSUN|DAY|DCLK|DDS|DE|DEAL|DEALER|DEALS|DEGREE|DELIVERY|DELL|DELOITTE|DELTA|DEMOCRAT|DENTAL|DENTIST|DESI|DESIGN|DEV|DHL|DIAMONDS|DIET|DIGITAL|DIRECT|DIRECTORY|DISCOUNT|DISCOVER|DISH|DIY|DJ|DK|DM|DNP|DO|DOCS|DOCTOR|DOG|DOMAINS|DOT|DOWNLOAD|DRIVE|DTV|DUBAI|DUCK|DUNLOP|DUPONT|DURBAN|DVAG|DVR|DZ|EARTH|EAT|EC|ECO|EDEKA|EDU|EDUCATION|EE|EG|EMAIL|EMERCK|ENERGY|ENGINEER|ENGINEERING|ENTERPRISES|EPSON|EQUIPMENT|ER|ERICSSON|ERNI|ES|ESQ|ESTATE|ESURANCE|ET|ETISALAT|EU|EUROVISION|EUS|EVENTS|EXCHANGE|EXPERT|EXPOSED|EXPRESS|EXTRASPACE|FAGE|FAIL|FAIRWINDS|FAITH|FAMILY|FAN|FANS|FARM|FARMERS|FASHION|FAST|FEDEX|FEEDBACK|FERRARI|FERRERO|FI|FIAT|FIDELITY|FIDO|FILM|FINAL|FINANCE|FINANCIAL|FIRE|FIRESTONE|FIRMDALE|FISH|FISHING|FIT|FITNESS|FJ|FK|FLICKR|FLIGHTS|FLIR|FLORIST|FLOWERS|FLY|FM|FO|FOO|FOOD|FOODNETWORK|FOOTBALL|FORD|FOREX|FORSALE|FORUM|FOUNDATION|FOX|FR|FREE|FRESENIUS|FRL|FROGANS|FRONTDOOR|FRONTIER|FTR|FUJITSU|FUJIXEROX|FUN|FUND|FURNITURE|FUTBOL|FYI|GA|GAL|GALLERY|GALLO|GALLUP|GAME|GAMES|GAP|GARDEN|GAY|GB|GBIZ|GD|GDN|GE|GEA|GENT|GENTING|GEORGE|GF|GG|GGEE|GH|GI|GIFT|GIFTS|GIVES|GIVING|GL|GLADE|GLASS|GLE|GLOBAL|GLOBO|GM|GMAIL|GMBH|GMO|GMX|GN|GODADDY|GOLD|GOLDPOINT|GOLF|GOO|GOODYEAR|GOOG|GOOGLE|GOP|GOT|GOV|GP|GQ|GR|GRAINGER|GRAPHICS|GRATIS|GREEN|GRIPE|GROCERY|GROUP|GS|GT|GU|GUARDIAN|GUCCI|GUGE|GUIDE|GUITARS|GURU|GW|GY|HAIR|HAMBURG|HANGOUT|HAUS|HBO|HDFC|HDFCBANK|HEALTH|HEALTHCARE|HELP|HELSINKI|HERE|HERMES|HGTV|HIPHOP|HISAMITSU|HITACHI|HIV|HK|HKT|HM|HN|HOCKEY|HOLDINGS|HOLIDAY|HOMEDEPOT|HOMEGOODS|HOMES|HOMESENSE|HONDA|HORSE|HOSPITAL|HOST|HOSTING|HOT|HOTELES|HOTELS|HOTMAIL|HOUSE|HOW|HR|HSBC|HT|HU|HUGHES|HYATT|HYUNDAI|IBM|ICBC|ICE|ICU|ID|IE|IEEE|IFM|IKANO|IL|IM|IMAMAT|IMDB|IMMO|IMMOBILIEN|IN|INC|INDUSTRIES|INFINITI|INFO|ING|INK|INSTITUTE|INSURANCE|INSURE|INT|INTEL|INTERNATIONAL|INTUIT|INVESTMENTS|IO|IPIRANGA|IQ|IR|IRISH|IS|ISMAILI|IST|ISTANBUL|IT|ITAU|ITV|IVECO|JAGUAR|JAVA|JCB|JCP|JE|JEEP|JETZT|JEWELRY|JIO|JLL|JM|JMP|JNJ|JO|JOBS|JOBURG|JOT|JOY|JP|JPMORGAN|JPRS|JUEGOS|JUNIPER|KAUFEN|KDDI|KE|KERRYHOTELS|KERRYLOGISTICS|KERRYPROPERTIES|KFH|KG|KH|KI|KIA|KIM|KINDER|KINDLE|KITCHEN|KIWI|KM|KN|KOELN|KOMATSU|KOSHER|KP|KPMG|KPN|KR|KRD|KRED|KUOKGROUP|KW|KY|KYOTO|KZ|LA|LACAIXA|LAMBORGHINI|LAMER|LANCASTER|LANCIA|LAND|LANDROVER|LANXESS|LASALLE|LAT|LATINO|LATROBE|LAW|LAWYER|LB|LC|LDS|LEASE|LECLERC|LEFRAK|LEGAL|LEGO|LEXUS|LGBT|LI|LIDL|LIFE|LIFEINSURANCE|LIFESTYLE|LIGHTING|LIKE|LILLY|LIMITED|LIMO|LINCOLN|LINDE|LINK|LIPSY|LIVE|LIVING|LIXIL|LK|LLC|LLP|LOAN|LOANS|LOCKER|LOCUS|LOFT|LOL|LONDON|LOTTE|LOTTO|LOVE|LPL|LPLFINANCIAL|LR|LS|LT|LTD|LTDA|LU|LUNDBECK|LUPIN|LUXE|LUXURY|LV|LY|MA|MACYS|MADRID|MAIF|MAISON|MAKEUP|MAN|MANAGEMENT|MANGO|MAP|MARKET|MARKETING|MARKETS|MARRIOTT|MARSHALLS|MASERATI|MATTEL|MBA|MC|MCKINSEY|MD|ME|MED|MEDIA|MEET|MELBOURNE|MEME|MEMORIAL|MEN|MENU|MERCKMSD|METLIFE|MG|MH|MIAMI|MICROSOFT|MIL|MINI|MINT|MIT|MITSUBISHI|MK|ML|MLB|MLS|MM|MMA|MN|MO|MOBI|MOBILE|MODA|MOE|MOI|MOM|MONASH|MONEY|MONSTER|MORMON|MORTGAGE|MOSCOW|MOTO|MOTORCYCLES|MOV|MOVIE|MP|MQ|MR|MS|MSD|MT|MTN|MTR|MU|MUSEUM|MUTUAL|MV|MW|MX|MY|MZ|NA|NAB|NAGOYA|NAME|NATIONWIDE|NATURA|NAVY|NBA|NC|NE|NEC|NET|NETBANK|NETFLIX|NETWORK|NEUSTAR|NEW|NEWHOLLAND|NEWS|NEXT|NEXTDIRECT|NEXUS|NF|NFL|NG|NGO|NHK|NI|NICO|NIKE|NIKON|NINJA|NISSAN|NISSAY|NL|NO|NOKIA|NORTHWESTERNMUTUAL|NORTON|NOW|NOWRUZ|NOWTV|NP|NR|NRA|NRW|NTT|NU|NYC|NZ|OBI|OBSERVER|OFF|OFFICE|OKINAWA|OLAYAN|OLAYANGROUP|OLDNAVY|OLLO|OM|OMEGA|ONE|ONG|ONL|ONLINE|ONYOURSIDE|OOO|OPEN|ORACLE|ORANGE|ORG|ORGANIC|ORIGINS|OSAKA|OTSUKA|OTT|OVH|PA|PAGE|PANASONIC|PARIS|PARS|PARTNERS|PARTS|PARTY|PASSAGENS|PAY|PCCW|PE|PET|PF|PFIZER|PG|PH|PHARMACY|PHD|PHILIPS|PHONE|PHOTO|PHOTOGRAPHY|PHOTOS|PHYSIO|PICS|PICTET|PICTURES|PID|PIN|PING|PINK|PIONEER|PIZZA|PK|PL|PLACE|PLAY|PLAYSTATION|PLUMBING|PLUS|PM|PN|PNC|POHL|POKER|POLITIE|PORN|POST|PR|PRAMERICA|PRAXI|PRESS|PRIME|PRO|PROD|PRODUCTIONS|PROF|PROGRESSIVE|PROMO|PROPERTIES|PROPERTY|PROTECTION|PRU|PRUDENTIAL|PS|PT|PUB|PW|PWC|PY|QA|QPON|QUEBEC|QUEST|QVC|RACING|RADIO|RAID|RE|READ|REALESTATE|REALTOR|REALTY|RECIPES|RED|REDSTONE|REDUMBRELLA|REHAB|REISE|REISEN|REIT|RELIANCE|REN|RENT|RENTALS|REPAIR|REPORT|REPUBLICAN|REST|RESTAURANT|REVIEW|REVIEWS|REXROTH|RICH|RICHARDLI|RICOH|RIGHTATHOME|RIL|RIO|RIP|RMIT|RO|ROCHER|ROCKS|RODEO|ROGERS|ROOM|RS|RSVP|RU|RUGBY|RUHR|RUN|RW|RWE|RYUKYU|SA|SAARLAND|SAFE|SAFETY|SAKURA|SALE|SALON|SAMSCLUB|SAMSUNG|SANDVIK|SANDVIKCOROMANT|SANOFI|SAP|SARL|SAS|SAVE|SAXO|SB|SBI|SBS|SC|SCA|SCB|SCHAEFFLER|SCHMIDT|SCHOLARSHIPS|SCHOOL|SCHULE|SCHWARZ|SCIENCE|SCJOHNSON|SCOR|SCOT|SD|SE|SEARCH|SEAT|SECURE|SECURITY|SEEK|SELECT|SENER|SERVICES|SES|SEVEN|SEW|SEX|SEXY|SFR|SG|SH|SHANGRILA|SHARP|SHAW|SHELL|SHIA|SHIKSHA|SHOES|SHOP|SHOPPING|SHOUJI|SHOW|SHOWTIME|SHRIRAM|SI|SILK|SINA|SINGLES|SITE|SJ|SK|SKI|SKIN|SKY|SKYPE|SL|SLING|SM|SMART|SMILE|SN|SNCF|SO|SOCCER|SOCIAL|SOFTBANK|SOFTWARE|SOHU|SOLAR|SOLUTIONS|SONG|SONY|SOY|SPACE|SPORT|SPOT|SPREADBETTING|SR|SRL|SS|ST|STADA|STAPLES|STAR|STATEBANK|STATEFARM|STC|STCGROUP|STOCKHOLM|STORAGE|STORE|STREAM|STUDIO|STUDY|STYLE|SU|SUCKS|SUPPLIES|SUPPLY|SUPPORT|SURF|SURGERY|SUZUKI|SV|SWATCH|SWIFTCOVER|SWISS|SX|SY|SYDNEY|SYMANTEC|SYSTEMS|SZ|TAB|TAIPEI|TALK|TAOBAO|TARGET|TATAMOTORS|TATAR|TATTOO|TAX|TAXI|TC|TCI|TD|TDK|TEAM|TECH|TECHNOLOGY|TEL|TEMASEK|TENNIS|TEVA|TF|TG|TH|THD|THEATER|THEATRE|TIAA|TICKETS|TIENDA|TIFFANY|TIPS|TIRES|TIROL|TJ|TJMAXX|TJX|TK|TKMAXX|TL|TM|TMALL|TN|TO|TODAY|TOKYO|TOOLS|TOP|TORAY|TOSHIBA|TOTAL|TOURS|TOWN|TOYOTA|TOYS|TR|TRADE|TRADING|TRAINING|TRAVEL|TRAVELCHANNEL|TRAVELERS|TRAVELERSINSURANCE|TRUST|TRV|TT|TUBE|TUI|TUNES|TUSHU|TV|TVS|TW|TZ|UA|UBANK|UBS|UG|UK|UNICOM|UNIVERSITY|UNO|UOL|UPS|US|UY|UZ|VA|VACATIONS|VANA|VANGUARD|VC|VE|VEGAS|VENTURES|VERISIGN|VERSICHERUNG|VET|VG|VI|VIAJES|VIDEO|VIG|VIKING|VILLAS|VIN|VIP|VIRGIN|VISA|VISION|VIVA|VIVO|VLAANDEREN|VN|VODKA|VOLKSWAGEN|VOLVO|VOTE|VOTING|VOTO|VOYAGE|VU|VUELOS|WALES|WALMART|WALTER|WANG|WANGGOU|WATCH|WATCHES|WEATHER|WEATHERCHANNEL|WEBCAM|WEBER|WEBSITE|WED|WEDDING|WEIBO|WEIR|WF|WHOSWHO|WIEN|WIKI|WILLIAMHILL|WIN|WINDOWS|WINE|WINNERS|WME|WOLTERSKLUWER|WOODSIDE|WORK|WORKS|WORLD|WOW|WS|WTC|WTF|XBOX|XEROX|XFINITY|XIHUAN|XIN|XN--11B4C3D|XN--1CK2E1B|XN--1QQW23A|XN--2SCRJ9C|XN--30RR7Y|XN--3BST00M|XN--3DS443G|XN--3E0B707E|XN--3HCRJ9C|XN--3OQ18VL8PN36A|XN--3PXU8K|XN--42C2D9A|XN--45BR5CYL|XN--45BRJ9C|XN--45Q11C|XN--4GBRIM|XN--54B7FTA0CC|XN--55QW42G|XN--55QX5D|XN--5SU34J936BGSG|XN--5TZM5G|XN--6FRZ82G|XN--6QQ986B3XL|XN--80ADXHKS|XN--80AO21A|XN--80AQECDR1A|XN--80ASEHDB|XN--80ASWG|XN--8Y0A063A|XN--90A3AC|XN--90AE|XN--90AIS|XN--9DBQ2A|XN--9ET52U|XN--9KRT00A|XN--B4W605FERD|XN--BCK1B9A5DRE4C|XN--C1AVG|XN--C2BR7G|XN--CCK2B3B|XN--CG4BKI|XN--CLCHC0EA0B2G2A9GCD|XN--CZR694B|XN--CZRS0T|XN--CZRU2D|XN--D1ACJ3B|XN--D1ALF|XN--E1A4C|XN--ECKVDTC9D|XN--EFVY88H|XN--FCT429K|XN--FHBEI|XN--FIQ228C5HS|XN--FIQ64B|XN--FIQS8S|XN--FIQZ9S|XN--FJQ720A|XN--FLW351E|XN--FPCRJ9C3D|XN--FZC2C9E2C|XN--FZYS8D69UVGM|XN--G2XX48C|XN--GCKR3F0F|XN--GECRJ9C|XN--GK3AT1E|XN--H2BREG3EVE|XN--H2BRJ9C|XN--H2BRJ9C8C|XN--HXT814E|XN--I1B6B1A6A2E|XN--IMR513N|XN--IO0A7I|XN--J1AEF|XN--J1AMH|XN--J6W193G|XN--JLQ61U9W7B|XN--JVR189M|XN--KCRX77D1X4A|XN--KPRW13D|XN--KPRY57D|XN--KPU716F|XN--KPUT3I|XN--L1ACC|XN--LGBBAT1AD8J|XN--MGB9AWBF|XN--MGBA3A3EJT|XN--MGBA3A4F16A|XN--MGBA7C0BBN0A|XN--MGBAAKC7DVF|XN--MGBAAM7A8H|XN--MGBAB2BD|XN--MGBAH1A3HJKRD|XN--MGBAI9AZGQP6J|XN--MGBAYH7GPA|XN--MGBBH1A|XN--MGBBH1A71E|XN--MGBC0A9AZCG|XN--MGBCA7DZDO|XN--MGBCPQ6GPA1A|XN--MGBERP4A5D4AR|XN--MGBGU82A|XN--MGBI4ECEXP|XN--MGBPL2FH|XN--MGBT3DHD|XN--MGBTX2B|XN--MGBX4CD0AB|XN--MIX891F|XN--MK1BU44C|XN--MXTQ1M|XN--NGBC5AZD|XN--NGBE9E0A|XN--NGBRX|XN--NODE|XN--NQV7F|XN--NQV7FS00EMA|XN--NYQY26A|XN--O3CW4H|XN--OGBPF8FL|XN--OTU796D|XN--P1ACF|XN--P1AI|XN--PBT977C|XN--PGBS0DH|XN--PSSY2U|XN--Q7CE6A|XN--Q9JYB4C|XN--QCKA1PMC|XN--QXA6A|XN--QXAM|XN--RHQV96G|XN--ROVU88B|XN--RVC1E0AM3E|XN--S9BRJ9C|XN--SES554G|XN--T60B56A|XN--TCKWE|XN--TIQ49XQYJ|XN--UNUP4Y|XN--VERMGENSBERATER-CTB|XN--VERMGENSBERATUNG-PWB|XN--VHQUV|XN--VUQ861B|XN--W4R85EL8FHU5DNRA|XN--W4RS40L|XN--WGBH1C|XN--WGBL6A|XN--XHQ521B|XN--XKC2AL3HYE2A|XN--XKC2DL3A5EE0H|XN--Y9A3AQ|XN--YFRO4I67O|XN--YGBI2AMMX|XN--ZFR164B|XXX|XYZ|YACHTS|YAHOO|YAMAXUN|YANDEX|YE|YODOBASHI|YOGA|YOKOHAMA|YOU|YOUTUBE|YT|YUN|ZA|ZAPPOS|ZARA|ZERO|ZIP|ZM|ZONE|ZUERICH|ZW|TEST)";
	});

	unwrapExports(tlds);
	var tlds_1 = tlds.TLDs;

	var dictionary = createCommonjsModule(function (module, exports) {
	Object.defineProperty(exports, "__esModule", { value: true });

	exports.openingParenthesis = "([\"'{";
	exports.closingParenthesis = ")]\"'}";
	exports.parenthesis = exports.openingParenthesis
	    .split("")
	    .map(function (x, i) { return "" + x + exports.closingParenthesis.charAt(i); });
	exports.htmlAttributes = [
	    "src",
	    "data",
	    "href",
	    "cite",
	    "formaction",
	    "icon",
	    "manifest",
	    "poster",
	    "codebase",
	    "background",
	    "profile",
	    "usemap",
	    "itemtype",
	    "action",
	    "longdesc",
	    "classid",
	    "archive"
	];
	exports.nonLatinAlphabetRanges = "\\u0041-\\u005A\\u0061-\\u007A\\u00AA\\u00B5\\u00BA\\u00C0-\\u00D6\\u00D8-\\u00F6\\u00F8-\\u02C1\\u02C6-\\u02D1\\u02E0-\\u02E4\\u02EC\\u02EE\\u0370-\\u0374\\u0376\\u0377\\u037A-\\u037D\\u0386\\u0388-\\u038A\\u038C\\u038E-\\u03A1\\u03A3-\\u03F5\\u03F7-\\u0481\\u048A-\\u0527\\u0531-\\u0556\\u0559\\u0561-\\u0587\\u05D0-\\u05EA\\u05F0-\\u05F2\\u0620-\\u064A\\u066E\\u066F\\u0671-\\u06D3\\u06D5\\u06E5\\u06E6\\u06EE\\u06EF\\u06FA-\\u06FC\\u06FF\\u0710\\u0712-\\u072F\\u074D-\\u07A5\\u07B1\\u07CA-\\u07EA\\u07F4\\u07F5\\u07FA\\u0800-\\u0815\\u081A\\u0824\\u0828\\u0840-\\u0858\\u08A0\\u08A2-\\u08AC\\u0904-\\u0939\\u093D\\u0950\\u0958-\\u0961\\u0971-\\u0977\\u0979-\\u097F\\u0985-\\u098C\\u098F\\u0990\\u0993-\\u09A8\\u09AA-\\u09B0\\u09B2\\u09B6-\\u09B9\\u09BD\\u09CE\\u09DC\\u09DD\\u09DF-\\u09E1\\u09F0\\u09F1\\u0A05-\\u0A0A\\u0A0F\\u0A10\\u0A13-\\u0A28\\u0A2A-\\u0A30\\u0A32\\u0A33\\u0A35\\u0A36\\u0A38\\u0A39\\u0A59-\\u0A5C\\u0A5E\\u0A72-\\u0A74\\u0A85-\\u0A8D\\u0A8F-\\u0A91\\u0A93-\\u0AA8\\u0AAA-\\u0AB0\\u0AB2\\u0AB3\\u0AB5-\\u0AB9\\u0ABD\\u0AD0\\u0AE0\\u0AE1\\u0B05-\\u0B0C\\u0B0F\\u0B10\\u0B13-\\u0B28\\u0B2A-\\u0B30\\u0B32\\u0B33\\u0B35-\\u0B39\\u0B3D\\u0B5C\\u0B5D\\u0B5F-\\u0B61\\u0B71\\u0B83\\u0B85-\\u0B8A\\u0B8E-\\u0B90\\u0B92-\\u0B95\\u0B99\\u0B9A\\u0B9C\\u0B9E\\u0B9F\\u0BA3\\u0BA4\\u0BA8-\\u0BAA\\u0BAE-\\u0BB9\\u0BD0\\u0C05-\\u0C0C\\u0C0E-\\u0C10\\u0C12-\\u0C28\\u0C2A-\\u0C33\\u0C35-\\u0C39\\u0C3D\\u0C58\\u0C59\\u0C60\\u0C61\\u0C85-\\u0C8C\\u0C8E-\\u0C90\\u0C92-\\u0CA8\\u0CAA-\\u0CB3\\u0CB5-\\u0CB9\\u0CBD\\u0CDE\\u0CE0\\u0CE1\\u0CF1\\u0CF2\\u0D05-\\u0D0C\\u0D0E-\\u0D10\\u0D12-\\u0D3A\\u0D3D\\u0D4E\\u0D60\\u0D61\\u0D7A-\\u0D7F\\u0D85-\\u0D96\\u0D9A-\\u0DB1\\u0DB3-\\u0DBB\\u0DBD\\u0DC0-\\u0DC6\\u0E01-\\u0E30\\u0E32\\u0E33\\u0E40-\\u0E46\\u0E81\\u0E82\\u0E84\\u0E87\\u0E88\\u0E8A\\u0E8D\\u0E94-\\u0E97\\u0E99-\\u0E9F\\u0EA1-\\u0EA3\\u0EA5\\u0EA7\\u0EAA\\u0EAB\\u0EAD-\\u0EB0\\u0EB2\\u0EB3\\u0EBD\\u0EC0-\\u0EC4\\u0EC6\\u0EDC-\\u0EDF\\u0F00\\u0F40-\\u0F47\\u0F49-\\u0F6C\\u0F88-\\u0F8C\\u1000-\\u102A\\u103F\\u1050-\\u1055\\u105A-\\u105D\\u1061\\u1065\\u1066\\u106E-\\u1070\\u1075-\\u1081\\u108E\\u10A0-\\u10C5\\u10C7\\u10CD\\u10D0-\\u10FA\\u10FC-\\u1248\\u124A-\\u124D\\u1250-\\u1256\\u1258\\u125A-\\u125D\\u1260-\\u1288\\u128A-\\u128D\\u1290-\\u12B0\\u12B2-\\u12B5\\u12B8-\\u12BE\\u12C0\\u12C2-\\u12C5\\u12C8-\\u12D6\\u12D8-\\u1310\\u1312-\\u1315\\u1318-\\u135A\\u1380-\\u138F\\u13A0-\\u13F4\\u1401-\\u166C\\u166F-\\u167F\\u1681-\\u169A\\u16A0-\\u16EA\\u1700-\\u170C\\u170E-\\u1711\\u1720-\\u1731\\u1740-\\u1751\\u1760-\\u176C\\u176E-\\u1770\\u1780-\\u17B3\\u17D7\\u17DC\\u1820-\\u1877\\u1880-\\u18A8\\u18AA\\u18B0-\\u18F5\\u1900-\\u191C\\u1950-\\u196D\\u1970-\\u1974\\u1980-\\u19AB\\u19C1-\\u19C7\\u1A00-\\u1A16\\u1A20-\\u1A54\\u1AA7\\u1B05-\\u1B33\\u1B45-\\u1B4B\\u1B83-\\u1BA0\\u1BAE\\u1BAF\\u1BBA-\\u1BE5\\u1C00-\\u1C23\\u1C4D-\\u1C4F\\u1C5A-\\u1C7D\\u1CE9-\\u1CEC\\u1CEE-\\u1CF1\\u1CF5\\u1CF6\\u1D00-\\u1DBF\\u1E00-\\u1F15\\u1F18-\\u1F1D\\u1F20-\\u1F45\\u1F48-\\u1F4D\\u1F50-\\u1F57\\u1F59\\u1F5B\\u1F5D\\u1F5F-\\u1F7D\\u1F80-\\u1FB4\\u1FB6-\\u1FBC\\u1FBE\\u1FC2-\\u1FC4\\u1FC6-\\u1FCC\\u1FD0-\\u1FD3\\u1FD6-\\u1FDB\\u1FE0-\\u1FEC\\u1FF2-\\u1FF4\\u1FF6-\\u1FFC\\u2071\\u207F\\u2090-\\u209C\\u2102\\u2107\\u210A-\\u2113\\u2115\\u2119-\\u211D\\u2124\\u2126\\u2128\\u212A-\\u212D\\u212F-\\u2139\\u213C-\\u213F\\u2145-\\u2149\\u214E\\u2183\\u2184\\u2C00-\\u2C2E\\u2C30-\\u2C5E\\u2C60-\\u2CE4\\u2CEB-\\u2CEE\\u2CF2\\u2CF3\\u2D00-\\u2D25\\u2D27\\u2D2D\\u2D30-\\u2D67\\u2D6F\\u2D80-\\u2D96\\u2DA0-\\u2DA6\\u2DA8-\\u2DAE\\u2DB0-\\u2DB6\\u2DB8-\\u2DBE\\u2DC0-\\u2DC6\\u2DC8-\\u2DCE\\u2DD0-\\u2DD6\\u2DD8-\\u2DDE\\u2E2F\\u3005\\u3006\\u3031-\\u3035\\u303B\\u303C\\u3041-\\u3096\\u309D-\\u309F\\u30A1-\\u30FA\\u30FC-\\u30FF\\u3105-\\u312D\\u3131-\\u318E\\u31A0-\\u31BA\\u31F0-\\u31FF\\u3400-\\u4DB5\\u4E00-\\u9FCC\\uA000-\\uA48C\\uA4D0-\\uA4FD\\uA500-\\uA60C\\uA610-\\uA61F\\uA62A\\uA62B\\uA640-\\uA66E\\uA67F-\\uA697\\uA6A0-\\uA6E5\\uA717-\\uA71F\\uA722-\\uA788\\uA78B-\\uA78E\\uA790-\\uA793\\uA7A0-\\uA7AA\\uA7F8-\\uA801\\uA803-\\uA805\\uA807-\\uA80A\\uA80C-\\uA822\\uA840-\\uA873\\uA882-\\uA8B3\\uA8F2-\\uA8F7\\uA8FB\\uA90A-\\uA925\\uA930-\\uA946\\uA960-\\uA97C\\uA984-\\uA9B2\\uA9CF\\uAA00-\\uAA28\\uAA40-\\uAA42\\uAA44-\\uAA4B\\uAA60-\\uAA76\\uAA7A\\uAA80-\\uAAAF\\uAAB1\\uAAB5\\uAAB6\\uAAB9-\\uAABD\\uAAC0\\uAAC2\\uAADB-\\uAADD\\uAAE0-\\uAAEA\\uAAF2-\\uAAF4\\uAB01-\\uAB06\\uAB09-\\uAB0E\\uAB11-\\uAB16\\uAB20-\\uAB26\\uAB28-\\uAB2E\\uABC0-\\uABE2\\uAC00-\\uD7A3\\uD7B0-\\uD7C6\\uD7CB-\\uD7FB\\uF900-\\uFA6D\\uFA70-\\uFAD9\\uFB00-\\uFB06\\uFB13-\\uFB17\\uFB1D\\uFB1F-\\uFB28\\uFB2A-\\uFB36\\uFB38-\\uFB3C\\uFB3E\\uFB40\\uFB41\\uFB43\\uFB44\\uFB46-\\uFBB1\\uFBD3-\\uFD3D\\uFD50-\\uFD8F\\uFD92-\\uFDC7\\uFDF0-\\uFDFB\\uFE70-\\uFE74\\uFE76-\\uFEFC\\uFF21-\\uFF3A\\uFF41-\\uFF5A\\uFF66-\\uFFBE\\uFFC2-\\uFFC7\\uFFCA-\\uFFCF\\uFFD2-\\uFFD7\\uFFDA-\\uFFDC";
	exports.TLDs = tlds.TLDs;
	});

	unwrapExports(dictionary);
	var dictionary_1 = dictionary.openingParenthesis;
	var dictionary_2 = dictionary.closingParenthesis;
	var dictionary_3 = dictionary.parenthesis;
	var dictionary_4 = dictionary.htmlAttributes;
	var dictionary_5 = dictionary.nonLatinAlphabetRanges;
	var dictionary_6 = dictionary.TLDs;

	var transform_1 = createCommonjsModule(function (module, exports) {
	Object.defineProperty(exports, "__esModule", { value: true });
	function applyOption(string, props, option) {
	    // conditional
	    if (typeof option === "function") {
	        return option(string, props);
	    }
	    // all
	    else {
	        return option;
	    }
	}
	function transform(input, options) {
	    var protocol = "";
	    var truncation = Infinity;
	    var attributes = {};
	    var truncateFromTheMiddle = false;
	    // special transformation
	    if (options && options.specialTransform) {
	        for (var index = 0; index < options.specialTransform.length; index++) {
	            var transformer = options.specialTransform[index];
	            if (transformer.test.test(input.string)) {
	                return transformer.transform(input.string, input);
	            }
	        }
	    }
	    // exclude
	    if (options && options.exclude) {
	        if (applyOption(input.string, input, options.exclude))
	            { return input.string; }
	    }
	    // protocol
	    if (options && options.protocol) {
	        protocol = applyOption(input.string, input, options.protocol);
	    }
	    if (input.protocol) {
	        protocol = "";
	    }
	    else if (!protocol) {
	        protocol = input.isEmail
	            ? "mailto:"
	            : input.isFile
	                ? "file:///"
	                : "http://";
	    }
	    // truncation
	    if (options && options.truncate) {
	        truncation = applyOption(input.string, input, options.truncate);
	    }
	    if (options && options.middleTruncation) {
	        truncateFromTheMiddle = applyOption(input.string, input, options.middleTruncation);
	    }
	    // attributes
	    if (options && options.attributes) {
	        attributes = applyOption(input.string, input, options.attributes);
	    }
	    return "<a " + Object.keys(attributes)
	        .map(function (key) {
	        return attributes[key] === true ? key : key + "=\"" + attributes[key] + "\" ";
	    })
	        .join(" ") + "href=\"" + protocol + input.string + "\">" + (input.string.length > truncation
	        ? truncateFromTheMiddle
	            ? input.string.substring(0, Math.floor(truncation / 2)) +
	                "…" +
	                input.string.substring(input.string.length - Math.ceil(truncation / 2), input.string.length)
	            : input.string.substring(0, truncation) + "…"
	        : input.string) + "</a>";
	}
	exports.transform = transform;
	});

	unwrapExports(transform_1);
	var transform_2 = transform_1.transform;

	var regex = createCommonjsModule(function (module, exports) {
	Object.defineProperty(exports, "__esModule", { value: true });

	var email_address = "([a-z0-9!#$%&'*+=?^_`{|}~-]+(\\.[a-z0-9!#$%&'*+=?^_`{|}~-]+)*)";
	var domainWithTLD = "([a-z0-9]+(-+[a-z0-9]+)*\\.)+(" + dictionary.TLDs + ")";
	var domainWithAnyTLD = "([a-z0-9]+(-+[a-z0-9]+)*\\.)+([a-z0-9][a-z0-9-]{0," + (Math.max.apply(commonjsGlobal, dictionary.TLDs.split("|").map(function (x) { return x.length; })) - 2) + "}[a-z0-9])";
	var allowedInPath = "a-zA-Z\\d\\-._~\\!$&*+,;=:@%'\"\\[\\]()";
	var path = "(((\\/(([" + allowedInPath + "]+(\\/[" + allowedInPath + "]*)*))?)?)((\\?([" + allowedInPath + "\\/?]*))?)((\\#([" + allowedInPath + "\\/?]*))?))?";
	var ipv4 = "((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)";
	var ipv6 = "\\[(([a-f0-9:]+:+)+[a-f0-9]+)\\]";
	var port = "(:(\\d{1,5}))?";
	var protocol = "(https?:|ftps?:)\\/\\/";
	var confirmedByProtocol = "(" + protocol + ")\\S+";
	var additionalSlashes = "(([\\/]?))+";
	var fqdn = "(((" + protocol + ")?(" + domainWithTLD + "|" + ipv4 + "|(" + protocol + ")(" + ipv6 + "|" + domainWithAnyTLD + "))(?!@\\w)" + port + ")|(" + confirmedByProtocol + "))";
	var nonLatinMatches = fqdn + "((((\\/(([" + allowedInPath + "]+(\\/[" + allowedInPath + dictionary.nonLatinAlphabetRanges + "]*)*))?)?)((\\?([" + allowedInPath + "\\/?]*))?)((\\#([" + allowedInPath + "\\/?]*))?))?\\b((([" + allowedInPath + "\\/" + dictionary.nonLatinAlphabetRanges + "][a-zA-Z\\d\\-_~+=\\/" + dictionary.nonLatinAlphabetRanges + "]+)?))+)";
	exports.email = "\\b(mailto:)?" + email_address + "@(" + domainWithTLD + "|" + ipv4 + ")\\b";
	exports.url = "(" + nonLatinMatches + ")|(\\b" + fqdn + path + "\\b" + additionalSlashes + ")";
	exports.file = "(file:\\/\\/\\/)([a-z]+:(\\/|\\\\)+)?([\\w.]+([\\/\\\\]?)+)+";
	exports.final = "(" + exports.url + ")|(" + exports.email + ")|(" + exports.file + ")";
	exports.finalRegex = new RegExp(exports.final, "gi");
	// for validation purposes
	exports.ipRegex = new RegExp("^(" + ipv4 + "|" + ipv6 + ")$", "i");
	exports.emailRegex = new RegExp("^(" + exports.email + ")$", "i");
	exports.fileRegex = new RegExp("^(" + exports.file + ")$", "i");
	exports.urlRegex = new RegExp("^(" + exports.url + ")$", "i");
	// identifying parts of the link
	var iidxes = {
	    isURL: 0,
	    isEmail: 0,
	    isFile: 0,
	    file: {
	        fileName: 0,
	        protocol: 0,
	    },
	    email: {
	        protocol: 0,
	        local: 0,
	        host: 0,
	    },
	    url: {
	        ipv4: 0,
	        ipv6: 0,
	        ipv4Confirmation: 0,
	        byProtocol: 0,
	        port: 0,
	        // three places where protocol can appear
	        protocol1: 0,
	        protocol2: 0,
	        protocol3: 0,
	        protocolWithDomain: 0,
	        path: 0,
	        // sometimes path might be split into two parts
	        secondPartOfPath: 0,
	        query: 0,
	        fragment: 0,
	    },
	};
	exports.iidxes = iidxes;
	var testers = [
	    "file:///some/file/path/filename.pdf",
	    "mailto:e+_mail.me@sub.domain.com",
	    "http://sub.domain.co.uk:3000/p/a/t/h_(asd)/h?q=abc123#dfdf",
	    "http://www.\u0639\u0631\u0628\u064A.com",
	    "http://127.0.0.1:3000/p/a/t_(asd)/h?q=abc123#dfdf",
	    "http://[2a00:1450:4025:401::67]/k/something",
	    "a.org/abc/\u10D8_\u10D2\u10D2" ].join(" ");
	var result = null;
	var i = 0;
	while ((result = exports.finalRegex.exec(testers)) !== null) {
	    if (i === 0) {
	        iidxes.isFile = result.lastIndexOf(result[0]);
	        iidxes.file.fileName = result.indexOf("filename.pdf");
	        iidxes.file.protocol = result.indexOf("file:///");
	    }
	    if (i === 1) {
	        iidxes.isEmail = result.lastIndexOf(result[0]);
	        iidxes.email.protocol = result.indexOf("mailto:");
	        iidxes.email.local = result.indexOf("e+_mail.me");
	        iidxes.email.host = result.indexOf("sub.domain.com");
	    }
	    if (i === 2) {
	        iidxes.isURL = result.lastIndexOf(result[0]);
	        iidxes.url.protocol1 = result.indexOf("http://");
	        iidxes.url.protocolWithDomain = result.indexOf("http://sub.domain.co.uk:3000");
	        iidxes.url.port = result.indexOf("3000");
	        iidxes.url.path = result.indexOf("/p/a/t/h_(asd)/h");
	        iidxes.url.query = result.indexOf("q=abc123");
	        iidxes.url.fragment = result.indexOf("dfdf");
	    }
	    if (i === 3) {
	        iidxes.url.byProtocol = result.lastIndexOf("http://www.عربي.com");
	        iidxes.url.protocol2 = result.lastIndexOf("http://");
	    }
	    if (i === 4) {
	        iidxes.url.ipv4 = result.indexOf("127.0.0.1");
	        iidxes.url.ipv4Confirmation = result.indexOf("0.");
	    }
	    if (i === 5) {
	        iidxes.url.ipv6 = result.indexOf("2a00:1450:4025:401::67");
	        iidxes.url.protocol3 = result.lastIndexOf("http://");
	    }
	    if (i === 6) {
	        iidxes.url.secondPartOfPath = result.indexOf("გგ");
	    }
	    i++;
	}
	});

	unwrapExports(regex);
	var regex_1 = regex.email;
	var regex_2 = regex.url;
	var regex_3 = regex.file;
	var regex_4 = regex.finalRegex;
	var regex_5 = regex.ipRegex;
	var regex_6 = regex.emailRegex;
	var regex_7 = regex.fileRegex;
	var regex_8 = regex.urlRegex;
	var regex_9 = regex.iidxes;

	var utils = createCommonjsModule(function (module, exports) {
	Object.defineProperty(exports, "__esModule", { value: true });

	function checkParenthesis(opening, closing, target, nextChar) {
	    if (nextChar !== closing) {
	        return false;
	    }
	    if (target.split(opening).length - target.split(closing).length === 1 ||
	        (opening === closing && target.split(opening).length % 2 === 0)) {
	        return true;
	    }
	}
	exports.checkParenthesis = checkParenthesis;
	exports.maximumAttrLength = dictionary.htmlAttributes.sort(function (a, b) { return b.length - a.length; })[0].length;
	function isInsideAttribute(prevFragment) {
	    return (/\s[a-z0-9-]+=('|")$/i.test(prevFragment) ||
	        /: ?url\(('|")?$/i.test(prevFragment));
	}
	exports.isInsideAttribute = isInsideAttribute;
	function isInsideAnchorTag(target, fullInput, targetEnd) {
	    var escapedTarget = target.replace(/[-\/\\^$*+?.()|[\]{}]/g, "\\$&");
	    var regex = new RegExp("(?=(<a))(?!([\\s\\S]*)(<\\/a>)(" + escapedTarget + "))[\\s\\S]*?(" + escapedTarget + ")(?!\"|')", "gi");
	    var result = null;
	    while ((result = regex.exec(fullInput)) !== null) {
	        var end = result.index + result[0].length;
	        if (end === targetEnd) {
	            return true;
	        }
	    }
	    return false;
	}
	exports.isInsideAnchorTag = isInsideAnchorTag;
	});

	unwrapExports(utils);
	var utils_1 = utils.checkParenthesis;
	var utils_2 = utils.maximumAttrLength;
	var utils_3 = utils.isInsideAttribute;
	var utils_4 = utils.isInsideAnchorTag;

	var node = createCommonjsModule(function (module, exports) {
	Object.defineProperty(exports, "__esModule", { value: true });




	var list = function (input) {
	    var found = [];
	    var result = null;
	    var _loop_1 = function () {
	        var start = result.index;
	        var end = start + result[0].length;
	        var string = result[0];
	        // ### trailing slashes problem
	        /**
	         * This is a quick and dirty fix for a problem that could be probably fixed with
	         * slight modification in the regex.
	         * The problem is that the library doesn't count the trailing slashes as part
	         * of the URL, unless there were multiple trailing slashes.
	         */
	        if (input.charAt(end) === "/") {
	            string = string + input.charAt(end);
	            end++;
	        }
	        // ### Parenthesis problem
	        /**
	                As we're using the \b to tokenize the URL, sometimes the parenthesis are part of the URL
	                and sometimes they are actually the last part, this makes the tokenization stops just
	                before them.
	                To fix this, we calculate how many parenthesis are open and how many are closed inside
	                the URL and based on the number we should be able to know whether the aforementioned
	                parenthesis character is part of the URL or not
	            */
	        if (dictionary.closingParenthesis.indexOf(input.charAt(end)) > -1) {
	            dictionary.parenthesis.forEach(function (str) {
	                var opening = str.charAt(0);
	                var closing = str.charAt(1);
	                if (utils.checkParenthesis(opening, closing, string, input.charAt(end))) {
	                    string = string + input.charAt(end);
	                    end++;
	                }
	            });
	        }
	        // ### HTML problem 1
	        /**
	                checking whether the token is already inside an HTML element by seeing if it's
	                preceded by an HTML attribute that would hold a url (e.g. scr, cite ...etc)
	            */
	        if (['""', "''", "()"].indexOf(input.charAt(start - 1) + input.charAt(end)) !== -1) {
	            if (utils.isInsideAttribute(input.substring(start - utils.maximumAttrLength - 15, start))) {
	                return "continue";
	            }
	        }
	        // ### HTML problem 2
	        /**
	                Checking whether the token is the content of an actual anchor
	                e.g. <a href="https://something.com">click to go to something.com and have fun</a>
	            */
	        if (input.substring(end, input.length).indexOf("</a>") > -1 &&
	            input.substring(0, start).indexOf("<a") > -1 &&
	            utils.isInsideAnchorTag(string, input, end)) {
	            return "continue";
	        }
	        if (result[regex.iidxes.isURL]) {
	            var path = (result[regex.iidxes.url.path] || "") +
	                (result[regex.iidxes.url.secondPartOfPath] || "") || undefined;
	            var protocol = result[regex.iidxes.url.protocol1] ||
	                result[regex.iidxes.url.protocol2] ||
	                result[regex.iidxes.url.protocol3];
	            found.push({
	                start: start,
	                end: end,
	                string: string,
	                isURL: true,
	                protocol: protocol,
	                port: result[regex.iidxes.url.port],
	                ipv4: result[regex.iidxes.url.ipv4Confirmation]
	                    ? result[regex.iidxes.url.ipv4]
	                    : undefined,
	                ipv6: result[regex.iidxes.url.ipv6],
	                host: result[regex.iidxes.url.byProtocol]
	                    ? undefined
	                    : (result[regex.iidxes.url.protocolWithDomain] || "").substr((protocol || "").length),
	                confirmedByProtocol: !!result[regex.iidxes.url.byProtocol],
	                path: result[regex.iidxes.url.byProtocol] ? undefined : path,
	                query: result[regex.iidxes.url.query] || undefined,
	                fragment: result[regex.iidxes.url.fragment] || undefined,
	            });
	        }
	        else if (result[regex.iidxes.isFile]) {
	            var filePath = string.substr(8);
	            found.push({
	                start: start,
	                end: end,
	                string: string,
	                isFile: true,
	                protocol: result[regex.iidxes.file.protocol],
	                filename: result[regex.iidxes.file.fileName],
	                filePath: filePath,
	                fileDirectory: filePath.substr(0, filePath.length - result[regex.iidxes.file.fileName].length),
	            });
	        }
	        else if (result[regex.iidxes.isEmail]) {
	            found.push({
	                start: start,
	                end: end,
	                string: string,
	                isEmail: true,
	                local: result[regex.iidxes.email.local],
	                protocol: result[regex.iidxes.email.protocol],
	                host: result[regex.iidxes.email.host],
	            });
	        }
	        else {
	            found.push({
	                start: start,
	                end: end,
	                string: string,
	            });
	        }
	    };
	    while ((result = regex.finalRegex.exec(input)) !== null) {
	        _loop_1();
	    }
	    return found;
	};
	var anchorme = function (arg) {
	    var _a = typeof arg === "string"
	        ? { input: arg, options: undefined, extensions: undefined }
	        : arg, input = _a.input, options = _a.options, extensions = _a.extensions;
	    if (extensions) {
	        for (var index = 0; index < extensions.length; index++) {
	            var extension = extensions[index];
	            input = input.replace(extension.test, extension.transform);
	        }
	    }
	    var found = list(input);
	    var newStr = "";
	    // the following code isn't very intuitive nor human readable
	    // but faster than others
	    for (var index = 0; index < found.length; index++) {
	        newStr =
	            (newStr
	                ? newStr
	                : index === 0
	                    ? input.substring(0, found[index].start)
	                    : "") +
	                transform_1.transform(found[index], options) +
	                (found[index + 1]
	                    ? input.substring(found[index].end, found[index + 1].start)
	                    : input.substring(found[index].end));
	    }
	    return newStr ? newStr : input;
	};
	anchorme.list = function (input) {
	    return list(input);
	};
	anchorme.validate = {
	    ip: function (input) { return regex.ipRegex.test(input); },
	    email: function (input) { return regex.emailRegex.test(input); },
	    file: function (input) { return regex.fileRegex.test(input); },
	    url: function (input) { return regex.urlRegex.test(input) || regex.ipRegex.test(input); },
	};
	exports.default = anchorme;
	});

	var index = unwrapExports(node);

	return index;

})));
