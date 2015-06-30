#include "tintiro.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;

GameMain::GameMain(){
	n = 0;
}

Player::Player(){
	money = 100;
	legth = 0;
	play = false;
	win = false;
}

void Player::parent(int order){
	if (play == true){
		cout << "あなたの所持金 " << money << "万円" << endl;
		cout << "あなたが親です、持ち金を設定してください --> ";
		cin >> legth;
		if (legth > money){
			cout << "所持金を超えます" << endl;
			parent(order);
			return;
		}
		cout << "親の持ち金は" << legth << "万円になりました" << endl;
	}else{
		cout << "コンピュータ" << order << "が親です" << endl;
		legth = rand() % 100 + 1;
		if (legth > money){
			parent(order);
			return;
		}
		cout << "親の持ち金は" << legth << "万円になりました" << endl;
	}
}

void Player::child(int n, int a){
	if (play == true){
		cout << "あなたの所持金 " << money << "万円" << endl;
		cout << "あなたは子です、賭け金を設定してください --> ";
		cin >> legth;
		if (legth > a || legth > money){
			cout << "所持金または親の持ち金を超えます" << endl;
			child(n,a);
			return;
		}
		cout << "あなたの賭け金は" << legth << "万円になりました" << endl;
	}else{
		legth = rand() % 100 + 1;
		if (legth > a || legth > money){
			child(n,a);
			return;
		}
		cout << "コンピュータ" << n << "は" << legth << "万円賭けました" << endl;
	}
}

void Player::batlle(int n){
	if (rand() % 2 == 0){
		if (play == true){
			cout << "あなたは勝ちました" << endl;
		}else{
			cout << "コンピュータ" << n << "は勝ちました" << endl;
		}
		win = true;
	}else{
		if (play == true){
			cout << "あなたは負けました" << endl;
		}else{
			cout << "コンピュータ" << n << "は負けました" << endl;
		}
		win = false;
	}
}

void Player::deduction(int n){
	if (win == true){
		money += legth;
	}else{
		money -= legth;
	}
}

void Player::states(int n){
	if (n == 0){
		cout << "あなたの残り所持金" << money << "万円" << endl;
	}else{
		cout << "コンピュータ" << n << "の残り所持金" << money << "万円" << endl;
	}
}

void GameMain::story(){
	cout << "何人で遊びますか？ --> " << flush;
	cin >> n;

	Player * player = new Player[n];
	player[0].play = true; //player[0]をプレイヤーとしてtrueする

	srand((unsigned int)time(NULL));
	int order = rand() % n;
	//while(){
		for (int i = 0; i < 3; ++i){
			player[order].parent(order);
			for (int i = 0; i < n; ++i){
				if (order != i || player[order].legth > 0){
					cout << "残り親の持ち金" << player[order].legth << "万円" << endl;
					player[i].child(i, player[order].legth);
					player[order].legth -= player[i].legth;
				}
			}
			cout << endl;

			for (int i = 0; i < n; ++i){
				if (order != i){
					player[i].batlle(i);
				}
			}
			cout << endl;

			for (int i = 0; i < n; ++i){
				if (order != i){
					player[i].deduction(i);
					if(player[i].win == true){
						player[order].money -= player[i].legth;
					}else{
						player[order].money += player[i].legth;
					}
				}
			}
			cout << endl;

			for (int i = 0; i < n; ++i){
				player[i].states(i);
			}
			cout << endl;
		}
		order++; //親交代
	//}
}

int main(){
	cout << "ちんちろりんを始めます" << endl;
	GameMain gm;
	gm.story();
}