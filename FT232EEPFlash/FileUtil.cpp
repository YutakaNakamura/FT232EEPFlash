#include "stdafx.h"
#include "FileUtil.h"

#include <iostream>
#include <fstream>

FileUtil::FileUtil()
{
}


FileUtil::~FileUtil()
{
}

bool FileUtil::WriteBinary(const std::string &filename, const std::vector<unsigned char> &pCharVec) {
	std::ofstream fout;

	//output to file
	fout.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	//  ファイルを開く
	//  ios::out は書き込み専用（省略可）
	//  ios::binary はバイナリ形式で出力（省略するとアスキー形式で出力）
	//  ios::truncはファイルを新規作成（省略可）
	//  ios::addにすると追記になる

	if (!fout) {
		std::cout << "ファイル" << filename << "が開けません";
		return 1;
	}
	//  ファイルが開けなかったときのエラー表示

	for (const auto& e : pCharVec) {
		fout.write((char *)&e, sizeof(char));
	}
	//	//文字列ではないデータをかきこむ
	//	// 「sizeof( double )」バイトの「char *」ポインタ「a[i]」をデータとして出力

	fout.close();  //ファイルを閉じる
	return 0;
}

bool FileUtil::ReadBinary(const std::string &filename, std::vector<unsigned char> &pOutputVec) {

	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	//  ファイルを開く
	//  ios::in は読み込み専用  ios::binary はバイナリ形式

	if (!fin) {
		std::cout << "ファイル" << filename << "が開けません" << std::endl;
		return 1;
	}
	//  ファイルが開けなかったときの対策

	char temp;  //文字列ではないデータ

	while (!fin.eof()) {  //ファイルの最後まで続ける
		fin.read((char *)&temp, sizeof(char));
		pOutputVec.push_back(temp);
		//文字列ではないデータを読みこむ
		//std::cout << temp << std::endl;
	}

	fin.close();  //ファイルを閉じる
	return 0;
}
