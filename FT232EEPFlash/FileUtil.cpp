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
	//  �t�@�C�����J��
	//  ios::out �͏������ݐ�p�i�ȗ��j
	//  ios::binary �̓o�C�i���`���ŏo�́i�ȗ�����ƃA�X�L�[�`���ŏo�́j
	//  ios::trunc�̓t�@�C����V�K�쐬�i�ȗ��j
	//  ios::add�ɂ���ƒǋL�ɂȂ�

	if (!fout) {
		std::cout << "�t�@�C��" << filename << "���J���܂���";
		return 1;
	}
	//  �t�@�C�����J���Ȃ������Ƃ��̃G���[�\��

	for (const auto& e : pCharVec) {
		fout.write((char *)&e, sizeof(char));
	}
	//	//������ł͂Ȃ��f�[�^����������
	//	// �usizeof( double )�v�o�C�g�́uchar *�v�|�C���^�ua[i]�v���f�[�^�Ƃ��ďo��

	fout.close();  //�t�@�C�������
	return 0;
}

bool FileUtil::ReadBinary(const std::string &filename, std::vector<unsigned char> &pOutputVec) {

	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	//  �t�@�C�����J��
	//  ios::in �͓ǂݍ��ݐ�p  ios::binary �̓o�C�i���`��

	if (!fin) {
		std::cout << "�t�@�C��" << filename << "���J���܂���" << std::endl;
		return 1;
	}
	//  �t�@�C�����J���Ȃ������Ƃ��̑΍�

	char temp;  //������ł͂Ȃ��f�[�^

	while (!fin.eof()) {  //�t�@�C���̍Ō�܂ő�����
		fin.read((char *)&temp, sizeof(char));
		pOutputVec.push_back(temp);
		//������ł͂Ȃ��f�[�^��ǂ݂���
		//std::cout << temp << std::endl;
	}

	fin.close();  //�t�@�C�������
	return 0;
}
