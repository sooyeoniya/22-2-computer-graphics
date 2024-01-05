# include <windows.h>
char* glkFileDlg(const char* filter) // 파일 다이얼로그를 띄워 파일 가져오기
{
	const int MaxLen = 1024;
	//static char fileName[MaxLen] = "";
	TCHAR fileName[MaxLen] = L"";

	OPENFILENAME open_file;
	memset(&open_file, 0, sizeof(OPENFILENAME));
	open_file.lStructSize = sizeof(OPENFILENAME);
	open_file.hwndOwner = NULL;
	//open_file.lpstrFilter = (LPCWSTR)filter;
	open_file.lpstrFilter = L"ASE 3D data (*.ase)\0*.ase\0All(*.*)\0*.*\0";
	open_file.nFilterIndex = 1;
	open_file.lpstrFile = fileName;
	open_file.nMaxFile = MaxLen;
	//open_file.nMaxCustFilter = MaxLen;
	open_file.lpstrTitle = L"Select a file";
	//open_file.lpstrDefExt = L"bvh";
	open_file.lpstrDefExt = L"ASE";
	open_file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	bool ret = GetOpenFileName(&open_file);

	return (ret) ? (char*)fileName : NULL;
}