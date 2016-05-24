#include <Wire.h>
extern "C" {
#include "user_interface.h"
}

// ATP3011 I2C Address
const uint8_t ADDR = 0x2E;

const int SENSOR_PIN = 13;

// 百人一首 読み
String data[] = {
  "a'kinotano-,karihono/iono,to'mao/ara'mi-  wa'gakoromodewa-,tu'yuni/nuretutu-", // 1
  "ha'rusugite- na'tukinikerashi-,shirotaeno-  koromoho'sucho-,a'mano/kaguyama-", // 2
  "ashibikino- yama'dorinoono,shidariono-  naganagashiyoo-,hitorikamonenn-", // 3
  "tagonourani- uchiidetemireba,shirotaeno-  fu'jinotakaneni-,yuki'wa/furitutu-", // 4
  "okuyamani- mo'miji/fumiwake,nakushikano-  ko'e/kikutokizo,a'kiwakanashiki-", // 5
  "kasasagino- wataseruhashini,okushimo'no-  si'rokio/mi'reba,yo'zo/fuke'ni/ke'ru-", // 6
  "amanohara- furisakemireba,ka'suganaru-  mikasanoyamani,i'desi/tuki'kamo-", // 7
  "wa'gaiowa- miyakonotatumi,shika'zo/su'mu-  yo'oujiyamato,hitowayu-nari-", // 8
  "hana'noirowa- uturinikerina,itadurani-  wa'gami/yo'ni/fu'ru,nagamesesimani-", // 9
  "koreyakono- yuku'mo/kae'rumo,waka'retewa-  siru'mo/sira'numo,o-sakanoseki-", // 10
  "watanohara- yasosimakakete,kogiidenuto-  hito'niwatugeyo,a'mano/turibune-", // 11
  "amatukaze- ku'mono/kayoiji,fukitojiyo-  oto'meno/su'gata,si'basi/todomen-", // 12
  "tukubaneno- mi'neyori/otu'ru,minano'gawa-  ko'izo/tumo'rite,futi'to/narinuru-", // 13
  "michinokuno- shino'bu/mojizuri,ta're/yue'ni-  mida're/some'nishi,wa're/narana'kuni-", // 14
  "kimigatame- ha'runo/no'niidete,wa'kana/tumu-  wa'ga/koro'modeni,yuki'wa/furitutu-", // 15
  "tachiwakare- i'nabano/yama'no,minenioru-  ma'tutoshi/ki'kaba,i'ma/kaerikon-", // 16
  "chihayaburu- kamiyomo/kikazu,tatutagawa-  karakurenaini,midukukurutowa-", // 17
  "suminoeno- kishi'ni/yorunami,yoru'/sa'eya-  yume'no/kayo'iji,hitomeyokuran-", // 18
  "naniwagata- miji'kaki/a'shino,fushinomamo-  awa'de/konoyoo,su'gu/shite'yotoya-", // 19
  "wabinureba- imahata/onaji,naniwanaru-  mio/tukushitemo,awantozoomo-", // 20
  "i'ma/ko'nnto- iisi/bakarini,nagatukino-  ariakeno/tuki'o,ma'ti/ide'turukana-", // 21
  "fu'kukarani- a'kino/kusakino,siorureba-  mube/yamakazeo,a'rasito/iuran-", // 22
  "tuki'/mireba- chi'jini/mono'koso,kanasikere-  wagami/hitotuno,a'kiniwa/aranedo-", // 23
  "konotabiwa- nusamo/toriaezu,tamukeyama-  mo'mijino/nishiki,ka'mino/manimani-", // 24
  "nanisiowaba- o-sakayamano,sanekadura-  hitoni/shirarede,kuru/yoshimogana-", // 25
  "ogurayama- mi'neno/momijiba,koko'ro/a'raba- i'ma/hitotabino,miyuki/matanan-", // 26
  "mikanohara- wakite/nagaruru,idumigawa-  itumikitoteka,ko'isi/karuran-", // 27
  "yamazatowa- fu'yuzo/sabisisa,masarikeru-  hitomemo/kusa'mo,karento/omo'eba-", // 28
  "kokoroateni- ora'baya/ora'n,hatusimono-  oki/madowaseru,shira'gikuno/hana-", // 29
  "ariakeno- turenaku/miesi,wakareyori-  akatukibakari,u'ki/monowanasi-", // 30
  "asaborake- ariakeno/tuki'to,mirumadeni-  yo'shinono/satoni,fureru/shira'yuki-", // 31
  "yamagawani- kazeno/kaketaru,sigaramiwa-  nagaremo/aenu,momiji/na'ri/ke'ri", // 32
  "hisakatano- hikarino/doke'ki,ha'runo/hi'ni-  shi'du/kokoronaku,hana'no/chiruran-", // 33
  "tareokamo- siru/hitonisen,takasagono-  ma'tumo/mukasino,to'mo/narana'kuni-", // 34
  "hito'waiza kokoromo/shirazu,furusatowa-  hana'zo/mukashino,ka'ni/nio'ikeru-", // 35
  "natu'no/yo'wa mada/yoinagara,akenuruo-  ku'mono/idukoni,tuki'yadoru/ra'n-", // 36
  "siratuyuni- kazeno/fukisiku,a'kino/no'wa-  turanukitomenu,tama'zo/chi'rikeru-", // 37
  "wasuraruru- mioba/omo'wazu,chika'itesi   hito'no/i'nochino,o'shikumo/arukana-", // 38
  "asaju-no- ononosinohara,sinoburedo-  amarite/na'doka,hito'no/koisiki-", // 39
  "sinoburedo- iro'ni/idenikeri,waga/ko'iwa-  monoya/omouto,hito'no/toumade-", // 40
  "koisucho- waganawa/madaki,tachinikeri-  hitoshirezukoso,omoisomesika-", // 41
  "chigi'rikina katamini/sodeo,simoritutu-  suenomatuyama,nami/kosaji/towa-", // 42
  "aimiteno- nochino/kokoroni,kurabureba-  mukasiwa/monoo,omowazarikeri-", // 43
  "aukotono- taetesinakuwa,nakanakuni-  hitoomo/miomo,uramizaramasi-", // 44
  "a'waretomo- iubeki/hitowa,omooede-  mino/itadurani,narinubekikana-", // 45
  "yuranotoo- wataru/funabito,kajiotae-  yukuemo/siranu,ko'ino/michikana-", // 46
  "yaemugura- sigereru/ya'dono,sabisikini-   hito'koso/miene,a'kiwa/kinikeri-", // 47
  "kazeo/itami- iwautu/namino,onorenomi-  kuda'kete/monoo,omoukorokana-", // 48
  "mikaki/moriejino/takuhino,yo'wa/moete   hiruwa/kietutu,monookoso/omo'e-", // 49
  "kimigatame- osikarazarisi,i'nochisae-  nagakumoganato,omoikerukana-", // 50
  "kakutodani- eyawaibukino,sasimokusa   sasimosirajina,moyuru/omo'io-", // 51
  "akenureba- kururumonotowa,sirinagara- na'o/urameshiki,asaborakekana-", // 52
  "nagekitutu- hitorinuruyono,akurumawa-  ikani/hisashiki,monotokawasiru-", // 53
  "wasurejino- yukusuemadewa,ka'takereba-  kyo'-o/kagirino,i'nochitomogana-", // 54
  "taki'no/oto'wa- ta'ete/hisa'siku/narinu'redo-  nako'so/nagarete,na'o/kiko'ekere-", // 55
  "arazaran- konoyono/hokano,omoideni- i'ma/hito'dabino,aukotomogana-", // 56
  "meguriaite- misiya/soretomo,wakanumani-  ku'moga/kurenisi,yowano/tuki'kana-", // 57
  "arimayama- inano/sakihara,kaze'/fu'keba-  idesoyohitoo,wasureyawasuru-", // 58
  "yasurawade- nenamasi/monoo,sa'yo/fu'kete-  katabu'ku/ma'deno,tuki'o/mi'sikana-", // 59
  "ohoeyama- ikunono/michino,to'okereba-  ma'da/fumi'momizu,a'mano/hashidate-", // 60
  "inisieno- na'rano/miyakono,yaeza'kura  kyo'-/kokonoeni,nioinurukana-", // 61
  "yo'o/ko'mete torino/soranewa,haka'rutomo   yo'ni/o-sakano,se'kiwayurusaji-", // 62
  "i'mawatada- omoitaenan,toba'kario   hitodutena'rade,iu/yosimogana-", // 63
  "asaborake- u'jino/kawagiri,taeda'eni-  arawa're/wata'ru se'zeno/ajirogi-", // 64
  "urami/wabi- osanu/sodeda'ni,a'rumonoo- ko'ini/kuchinan,na/ko'so/osikere-", // 65
  "morotomoni- a'wareto/omo'e,yamaza'kura   hanayori/hokani,siru/hitomo/nasi-", // 66
  "ha'runo/yo'no- yume/ba'karinaru,tamakurani-  ka'inaku/tatamu,nako'so/o'sikere-", // 67
  "kokoronimo- a'rade/ukiyoni,nagaraeba-  ko'ishikarubeki,yo'wano/tuki'kana-", // 68
  "a'rasi/fu'ku mimurono/yama'no,momijibawa  ta'tutano/kawa'no,ni'shiki/na'ri/ke'ri", // 69
  "sabishisani- ya'doo/ta'chi/i'dete,nagamu'reba-  i'dukomo/onaji,a'kino/yu-gure", // 70
  "yu-sareba- ka'dotano/i'naba,otodurete-  a'sino/maroyani,aki'kazezo/fu'ku-", // 71
  "otoni/kiku- ta'kasino/hama'no,adanamiwa-  kake'jiya/sodeno,nuremoko'sosure-", // 72
  "takasogono- o'noeno/sakura,saki'ni/ke'ri-  to'yamano/kasumi,tatazumo/aranan-", // 73
  "ukarikeru- hitoo/hatuseno,yamaorosiyo-  hagesikaretowa,inoranumono-", // 74
  "chigiriokisi- sasemoga/tu'yuo,i'nochinite-  awarekotoshino,a'kimo/inumeri-", // 75
  "watanohara- kogiidetemireba,hisakatano- kumoini/magau,okitu/shiranami-", // 76
  "se'o/haya'mi- iwa'ni/seka'ruru,taki'gawano-  waretemo/sue'ni,awa'ntozo/omo-", // 77
  "awajisima- kayou/chi'dorino,naku'/ko'eni- ikuyo/nezamenu,su'mano/sekimori-", // 78
  "aki'kazeni- tanabi'ku/ku'mono,taemayori-  moreiduru/tuki'no,ka'geno/sayakesa-", // 79
  "nagakaran- koko'romo/shirazu,kurokamino-  mida'rete/ke'sawa,mono'-/ko'so/omo'e", // 80
  "hototogisu- nakituru/katao,nagamureba-  ta'da/ariakeno,tuki'zo/noko'reru-", // 81
  "omo'i/wabi sa'temo/i'nochiwa,a'ru/monoo  u'kini/tae'nuwa,na'mida/na'ri/ke'ri", // 82
  "yononakayo- michikoso/nakere,omo'iiru-  yamano/okunimo,sikazo/nakunaru-", // 83
  "nagaraeba- mata/konogoroya,sinobaren-  usitomishiyozo,imawa/ko'ishiki-", // 84
  "yo'mo/sugara- monoomoukorowa,akeyarade- neyano/himasae,turenakarikeri-", // 85
  "nageketote- tuki'ya/hamonoo,omowasuru-  kakochigaonaru,wa'ga/na'midakana-", // 86
  "murasameno- tu'yumo/ma'da/i'nu,ma'kino/ha'ni  kiri/tachinoboru,a'kino/yu-gure", // 87
  "naniwaeno- a'sino/karineno,hitoyo/yue-  mio'/tuku'shiteya,ko'i/watarubeki-", // 88
  "tama'no/o'yo tae'naba/tae'ne,nagaraeba- sinobu'ru/kotono,yowa'rimozo/suru", // 89
  "misebayana- o'jimano/a'mano,sodeda'nimo-  nurenizonuresi,iro'wa/kawarazu", // 90
  "kirigirisu- naku'ya/shimoyono,samusironi- koromokatasiki,hitorikamonen-", // 91
  "wa'ga/sodewa sioini/mienu,okino/isino-  hitokoso/sirane,kawa'ku/mamonasi", // 92
  "yono'nakawa- tunenimo/gamona,nagisakogu-  a'mano/obuneno,tunade/kanasimo-", // 93
  "miyosinono- yamano/akikaze,sa'yo/fu'kete- furu'sato/sa'muku,koromoutunari-", // 94
  "ookenaku- ukiyono/ta'mini,ooukana-  wa'ga/ta'tu/so'mani,sumizomeno/sode", // 95
  "hana'/sasou,a'rasino/niwano,yuki/na'rade-  furiyukumonowa,wa'gami/na'ri/ke'ri", // 96
  "ko'nu/hitoo- matuhono/urano,yu-nagini-  yaku'ya/mo'shiono,mimo'/koga'retutu", // 97
  "kaze/soyo'gu- na'rano/ogawano,yu-gurewa-  misogizo/na'tuno,sirusi/na'ri/ke'ru", // 98
  "hitomooshi- hitomouramesi,ajikinaku-  yoo/omouyueni,mono/omoumiwa-", // 99
  "momoshikiya- furuki/nokibano,sinobunimo-  na'o/amariaru,mukashi/na'ri/ke'ri", // 100
  };

const int MAX = 100;
int max = 0;
int done[MAX];

void setup() {
  Serial.begin(115200);
  Serial.println("");
//Wire.begin(4, 5); // (SDA,SCL) Default
  Wire.begin(); // (SDA,SCL)

  for (int i = 0; i < MAX; i++) {
    done[i] = i;
  }

  long seed = system_adc_read() * system_adc_read();
  randomSeed(seed);

  pinMode(SENSOR_PIN, INPUT);

  delay(200);
}

void check_sensor() {
  bool isReady = digitalRead(SENSOR_PIN) == 0;
  bool onSpeak = isBusy();
  if (isReady && !onSpeak) {
    if (max == 0) max = MAX;
    int i = (int)random(max);
    int n = done[i];
    swap(done, i, --max);
    Serial.println(String("Now : ") + (MAX-max) + " No. : " + (n+1));
    delay(3000);
    speak(data[n]);
  }
  if (!isReady && onSpeak) {
    speak_stop();
  }
}

void swap(int *data, int a, int b) {
  if (a != b) {
    int tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
  }
}

void check_serial() {
  if (0 < Serial.available()) {
    delay(10);
    String buff;
    while (0 < Serial.available()) {
      char ch = Serial.read();
      if (ch == '\n') {
        speak(buff);
        Serial.println(buff);
      } else if (0x20 <= ch && ch <= 0x7f) {
        // ASCII文字コード
        buff = buff + ch;
      } else {
        // Do nothing
      }
    }
  }
}

void loop() {
//check_serial();
  check_sensor();
  delay(200);
}


bool isBusy() {
  Wire.requestFrom(ADDR, (uint8_t)1);
  while (true) {
    while (Wire.available()) {
      char b = Wire.read();
      // コマンド実行中は Busy 状態になり、この間に他のコマンドを受信すると、コマンド応答として '*' が返ります。
      // なお、発話中は Busy 状態となります。
      return b == '*';
    }
    delay(100);
  }
}

void speak_stop() {
  speak("$");
}

void speak(String buff) {

  uint8_t *data = (uint8_t *)buff.c_str();
  write_data(ADDR, data, buff.length());

  // １つのコマンドは 1byte～127byte の ASCII 文字列の最後にデリミタとして CR(0x0D)を付与します。
  // AT30110F4 は、この CR の受信後にコマンドを実行します。なお、コマンドの大文字、小文字は区別されます。

  uint8_t cmd[] = {0x0D};
  write_data(ADDR, cmd, 1);

  delay(1);
}

/////////

void write_data(uint8_t addr, uint8_t *data, size_t len) {
  // wireライブラリは最大32バイトなので分割して送信する
  const size_t max = 32;
  size_t n = len / max;
  size_t m = len % max;
  size_t i = 0;
  for (; i < n; i++) {
    write(addr, &data[i*max], max);
  }
  write(addr, &data[i*max], m);
  delay(1);
}

void write(uint8_t addr, uint8_t *data, size_t len) {
  Wire.beginTransmission(addr);
  Wire.write(data, len);
  Wire.endTransmission();
  delayMicroseconds(27); // 26.3us
}



