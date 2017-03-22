#ifndef _ae_mmLod_FILE
#define _ae_mmLod_FILE
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cstdio>
#include <boost/regex.hpp>
#include <boost/shared_ptr.hpp>
#include <Windows.h>

namespace angel {
	typedef std::vector<BYTE> LodData;
	typedef boost::shared_ptr<LodData> pLodData;


	class LodFile {
		private:
			typedef struct {
				FILE*		  f;
				std::string   name;
				std::string   dirname;
			} lod_file_t;
			typedef struct {
				int lodindex,off,size,version;
			} pak_item_t;
			std::vector<lod_file_t> paks;
			std::map<std::string, pak_item_t> files;
			pak_item_t FindFile(const std::string& fname);
			pLodData LoadMapFileData(const pak_item_t&);
			pLodData LoadSpritesFileData(const pak_item_t&);
			pLodData LoadSpritesFileHdr(const pak_item_t&);
		public:
			LodFile(){}
			~LodFile();
			bool  AddLod( const std::string& fname );
			bool  FileExist(const std::string& fname) {
				pak_item_t pitm = FindFile(fname);
				return pitm.size >=0;
			}
			pLodData LoadFile( const std::string& fname); //������ ��� ��� ���� � lod �����
			pLodData LoadFileData( const std::string& fname);//��� �������� � ����� ������������ �������������� �������
			pLodData LoadFileHdr( const std::string& fname);//������ ������ 0x20 ��� ����� (� mm8 language ��� �������� 0x40, � ��������� 0x10)
			pLodData LoadFileHdrName( const std::string& fname);//������ ���� ��������� � ������ 0x40 � mm8 lang, 0x10 � ���������
			int	  GetFileList( const boost::regex& re, std::vector <std::string>* filelist);	
			size_t GetNumPaks() {
				return paks.size();
			};
			size_t GetNumFiles() {
				return files.size();
			};
	};
	extern LodFile LodManager;
};
#endif //_ae_mmLod_FILE