#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <conio.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>
#include <mbctype.h>
#include <mbstring.h>
#include "rpg.h"

void prologue(void){
  printf("ここは私立元町学園・・・\n");
  sleep(1);
  printf("学生は平穏で怠惰な学園生活を送っていた\n");
  sleep(1);
  printf("しかし・・・\n");
  sleep(1);
  printf("突如として学園生活は一変する\n");
  sleep(1);
  printf("元町学園は魔界に引きずり込まれる・・・\n");
  sleep(1);
  printf("学生達は魔界から脱出出来るのか・・・!\n");
  sleep(1);
}

int check_player_name(Player **st){
  int i, error_count, char_count;

  error_count = 0;
  for ( i = 0; (*st) -> name[i] != '\0'; i++ ){
    //エラー判定が正確ではないがまだ正しく判定してくれるものであるから採用
    if ( isalnum( (*st) -> name[i] ) == 0 ){
      error_count++;
      printf("入力された文字がエラーです\n");
      char_count = 100;  //エラー値
      return char_count;
    }

    //以下未完のエラー処理
    /*if ( (*st) -> name[i] >= 0x40 && (*st) -> name[i] <= 0x7e){

    }
    else{
      error_count++;
      printf("入力された文字がエラーです\n");
      char_count = 100;  //エラー値
      return char_count;
    }*/

    //全角文字（漢字）の１文字を判定
    /*if ( _ismbblead( (*st) -> name[i] ) != 0 ){
      if ( (*st) -> name[i] == '\0' ){
        break;
      }
      error_count++;
      printf("入力された文字がエラーです\n");
      char_count = 100;  //エラー値
      return char_count;
    }
    else if ( _ismbbtrail( (*st) -> name[i] ) != 0 ){
      error_count++;
      printf("入力された文字がエラーです\n");
      char_count = 100;  //エラー値
      return char_count;
    }*/

  }

  if ( error_count == 0 ){
    // LC_CTYPE をネイティブロケールに変更
    if( setlocale( LC_CTYPE, "" ) == NULL ){
      fputs( "ロケールの設定に失敗しました。\n", stderr );
      exit( EXIT_FAILURE );
    }

    mbstate_t mbstate = {0};

    char_count = 0;
    for( i = 0; (*st) -> name[i] != '\0'; ++i ){
      size_t len1 = mbrlen( &(*st) -> name[i], 1, &mbstate );

      //printf("%zu\n", len1);

      if( len1 == (size_t)-1 ){
        // 有効な文字列ではない
        perror( "" );
        exit( EXIT_FAILURE );
      }
      if( len1 != (size_t)-2 ){
        // マルチバイト文字を構成するバイト列の途中でないなら、
        // １文字としてカウント
        char_count++;
      }
    }
    //ネイティブスケールをデフォルトに戻す
    setlocale( LC_CTYPE, "C" );
    printf("len:%d\n", char_count);
  }

  return char_count;
}

void game_start(Player *st, Player *st2, Player *st3){
  int input, len, char_count;

  printf("ゲームスタート！！\n");
  sleep(1);

  //主人公
  do {
    printf("あなたの名前を入力してください(6文字以内かつ半角英数字)\n");
    scanf("%s", st -> name);
    /*len = (int)strlen( st -> name);
    //printf("len:%d\n", len);
    if ( len > 12 ){
      printf("名前の文字数がオーバーしています!\n");
    }*/
    char_count = check_player_name(&st);
  }while ( char_count > 6 );

  printf("名前は%sでよろしいですか？\n", st -> name);
  printf("1:yes 2:no\n");
  printf("1か2を入力してください！\n");
  do {
    input = _getch();
    if ( input == '2' ){
      do{
        printf("あなたの名前を入力してください(6文字以内かつ半角英数字)\n");
        scanf("%s", st -> name);

        char_count = check_player_name(&st);
      } while ( char_count > 6 );
      setlocale( LC_CTYPE, "C" );
      printf("名前は%sでよろしいですか？\n", st -> name);
      printf("1:yes 2:no\n");
      printf("1か2を入力してください！\n");
      input = _getch();
    }
  } while( input != '1' );

  sleep(1);
  //2人目
  do {
    printf("２人目の名前を入力してください(6文字以内かつ半角英数字)\n");
    scanf("%s", st2 -> name);
    char_count = check_player_name(&st2);
  } while ( char_count > 6 );

  printf("名前は%sでよろしいですか？\n", st2 -> name);
  printf("1:yes 2:no\n");
  printf("1か2を入力してください！\n");
  do {
    input = _getch();
    if ( input == '2' ){
      do{
        printf("２人目の名前を入力してください(6文字以内かつ半角英数字)\n");
        scanf("%s", st2 -> name);

        char_count = check_player_name(&st2);
      } while ( char_count > 6 );
      setlocale( LC_CTYPE, "C" );
      printf("名前は%sでよろしいですか？\n", st2 -> name);
      printf("1:yes 2:no\n");
      printf("1か2を入力してください！\n");
      input = _getch();
    }
  } while( input != '1' );

  sleep(1);

  do {
    printf("３人目の名前を入力してください(6文字以内かつ半角英数字)\n");
    scanf("%s", st3 -> name);
    char_count = check_player_name(&st3);
  } while ( char_count > 6 );

  printf("名前は%sでよろしいですか？\n", st3 -> name);
  printf("1:yes 2:no\n");
  printf("1か2を入力してください！\n");
  do {
    input = _getch();
    if ( input == '2' ){
      do{
        printf("３人目の名前を入力してください(6文字以内かつ半角英数字)\n");
        scanf("%s", st3 -> name);

        char_count = check_player_name(&st3);
      } while ( char_count > 6 );
      setlocale( LC_CTYPE, "C" );
      printf("名前は%sでよろしいですか？\n", st3 -> name);
      printf("1:yes 2:no\n");
      printf("1か2を入力してください！\n");
      input = _getch();
    }
  } while( input != '1' );

  sleep(1);

}

void map_tutorial(void){
  int input;

  do{
    printf("RPGパートにおけるダンジョン探索のチュートリアルを紹介します\n");
    sleep(2);
    printf("ダンジョンに入ると画面上には3Dダンジョン画面と2Dマップが表示されます\n");
    sleep(2);
    printf("ダンジョンを移動するにはカーソルキー(方向キー、矢印キー)を押してください\n");
    sleep(2);
    printf("また、ダンジョン探索時にメニュー画面を開きたいときはmを押すことでメニュー画面が開かれます\n");
    sleep(1);
    printf("最後にオートマッピング機能について説明します\n");
    sleep(1);
    printf("ダンジョンを進むと自動的にマップが記録されていきます\n");
    sleep(1);
    printf("マップはメニュー画面から見ることが出来て、マップの*は既に訪れた箇所、Pは現在地を表しています\n");
    sleep(1);

    printf("チュートリアルをもう一回見ますか?\n");
    printf("1.YES 2.NO\n");
    printf("1か2を入力してください\n");
    input = _getch();

  }while ( input == '1' );

  printf("\n");
}

void game_story1(Player *st, Player *st2, Player *st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items, Area1 *area1, Enemy *enemy, Enemy *enemy1, Enemy *enemy2){

  st -> hp = 30;
  st -> maxhp = 30;
  st -> mp = 7;
  st -> maxmp = 7;
  st -> atk = 1;
  st -> magic = 1;
  st -> str = 1;
  st -> agi = 1;
  st -> luk = 1;
  st -> lv = 1;
  st -> exp = 0;
  st -> sumexp = 0;
  st -> nextexp = 10;
  st -> gold = 0;
  //badstatus = 0:正常
  //badstatus = 1:死亡
  //badstatus = 2:毒状態
  //badstatus = 3; 麻痺
  //badstatus = 4; 魅了
  //badstatus = 5; 魔封
  //badstatus = 6; 石化
  //badstatus = 7; 混乱
  //badstatus = 8; 睡眠
  //badstatus = 9; 呪い
  st -> badstatus = GOOD;
  //攻撃耐性
  st -> physical_attack = 100;
  st -> gun_attack = 100;
  st -> fire = 200;
  st -> ice = 50;
  st -> elec = 100;
  st -> wave = 100;
  st -> almighty = 100;
  st -> death = 100;
  st -> expel = 50;
  st -> poison = 100;
  st -> palyze = 100;
  st -> charm = 100;
  st -> close = 100;
  st -> stone = 100;
  st -> panic = 100;
  st -> sleep = 100;
  st -> curse = 100;
  st -> stage_clear = 0;

  st2 -> hp = 32;
  st2 -> maxhp = 32;
  st2 -> mp = 5;
  st2 -> maxmp = 5;
  st2 -> atk = 1;
  st2 -> magic = 1;
  st2 -> str = 1;
  st2 -> agi = 1;
  st2 -> luk = 1;
  st2 -> lv = 1;
  st2 -> exp = 0;
  st2 -> sumexp = 0;
  st2 -> nextexp = 10;
  st2 -> gold = 0;
  st2 -> badstatus = GOOD;
  //攻撃耐性
  st2 -> physical_attack = 100;
  st2 -> gun_attack = 100;
  st2 -> fire = 50;
  st2 -> ice = 200;
  st2 -> elec = 100;
  st2 -> wave = 100;
  st2 -> almighty = 100;
  st2 -> death = 100;
  st2 -> expel = 50;
  st2 -> poison = 100;
  st2 -> palyze = 100;
  st2 -> charm = 100;
  st2 -> close = 100;
  st2 -> stone = 100;
  st2 -> panic = 100;
  st2 -> sleep = 100;
  st2 -> curse = 100;
  st2 -> stage_clear = 0;

  st3 -> hp = 25;
  st3 -> maxhp = 25;
  st3 -> mp = 10;
  st3 -> maxmp = 10;
  st3 -> atk = 1;
  st3 -> magic = 1;
  st3 -> str = 1;
  st3 -> agi = 1;
  st3 -> luk = 1;
  st3 -> lv = 1;
  st3 -> exp = 0;
  st3 -> sumexp = 0;
  st3 -> nextexp = 10;
  st3 -> gold = 0;
  //badstatus = 0:正常
  //badstatus = 1:死亡
  //badstatus = 2:毒状態
  st3 -> badstatus = GOOD;
  //攻撃耐性
  st3 -> physical_attack = 100;
  st3 -> gun_attack = 100;
  st3 -> fire = 100;
  st3 -> ice = 100;
  st3 -> elec = 50;
  st3 -> wave = 200;
  st3 -> almighty = 100;
  st3 -> death = 100;
  st3 -> expel = 50;
  st3 -> poison = 100;
  st3 -> palyze = 100;
  st3 -> charm = 100;
  st3 -> close = 100;
  st3 -> stone = 100;
  st3 -> panic = 100;
  st3 -> sleep = 100;
  st3 -> curse = 100;
  st3 -> stage_clear = 0;

  /*printf("放課後・・・\n");
  sleep(2);
  printf("%s「%s、どっか遊びに行かない？」\n", st2 -> name, st -> name);
  sleep(2);
  printf("%s「自分も行きたい！」\n", st3 -> name);
  sleep(2);
  printf("%s「じゃあ、３人でゲーセン行こう！」\n", st2 -> name);
  sleep(2);
  printf("その時・・・\n");
  sleep(2);
  printf("窓から見える外の景色が一変した\n");
  sleep(2);
  printf("%s「何か雰囲気変わった？」\n", st3 -> name);
  sleep(2);
  printf("%s「確かに、%sも何か感じる？」\n", st2 -> name, st -> name);
  sleep(2);
  printf("\a");
  printf("クラスメイト「キャー－」\n");
  sleep(1);
  printf("クラスメイト「廊下に化け物が・・・」\n");
  sleep(2);
  printf("\a");
  printf("%s %s「廊下に行ってみよう！」\n", st2 -> name, st3 -> name);
  sleep(1);
  printf("3人は廊下へと向かった・・・\n");
  sleep(2);
  printf("ここからRPGパートが始まります\n");
  printf("その前に３人のステータスを表示します\n");
  sleep(2);*/
  display_status(&st, &st2, &st3);

  printf("\n");
  sleep(2);

  //map_tutorial();
  sleep(1);
  area1_map(&area1, &st, &st2, &st3, &player_skill, &player_skill2, &player_skill3, &items, &enemy, &enemy1, &enemy2);

  sleep(2);

  printf("\a");
  //printf("---STAGE1 CLEARED!!---\n");
  st -> stage_clear = 1;

  st -> badstatus = GOOD;
  st2 -> badstatus = GOOD;
  st3 -> badstatus = GOOD;

  st -> hp = st -> maxhp;
  st -> mp = st -> maxmp;
  st2 -> hp = st2 -> maxhp;
  st2 -> hp = st2 -> maxmp;
  st3 -> hp = st3 -> maxhp;
  st3 -> hp = st3 -> maxmp;

}

void game_story2(Player *st, Player *st2, Player * st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items){
  int input;
  printf("\n");
  printf("%sは冒険を続けている・・・\n", st -> name);
  printf("\a");
  printf("---STAGE2---\n");

  //display_status(&st);

  sleep(1);
  printf("目の前に回復の泉がある!\n");
  sleep(1);

  printf("回復しますか?(全回復:20GOLD)\n");
  printf("%sのGOLD:%d\n",st -> name, st -> gold);
  printf("1:yes 2:no\n");
  printf("1か2を入力してください!\n");
  input = getch();
  if ( input == '1' ){
    recover_event(&st);
    st -> gold -= 20;
    printf("%sのGOLD:%d -> %d\n", st -> name, st -> gold + 20, st -> gold);
  }
  if ( input == '2' ){
    printf("%sは回復の泉を後にして先を急いだ・・・\n", st -> name);
  }

  printf("\a");
  printf("---STAGE2 CLEARED!!---\n");
  st -> stage_clear  = 2;

  st -> hp = st -> maxhp;
  st -> mp = st -> maxmp;

}