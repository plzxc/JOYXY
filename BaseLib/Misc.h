#ifndef __MISC_H__
#define __MISC_H__
#include <string>
#include <vector>
using namespace std;

#define SAFE_DELETE(p) delete (p); (p) = NULL;
#define SAFE_DELETE_ARRAY(p) delete[] (p); (p) = NULL;

#define MAX_USER_PACK_SIZE	50 * 1024	// 用户封包，单个包的最大字节数

#define MAX_USER_RECV_SIZE	MAX_USER_PACK_SIZE * 100 	// 接收缓存数据大小

#define BUFF_CMD(ptr,type)    \
	char buffer##type[MAX_USER_PACK_SIZE];     \
	memset(buffer##type,0,MAX_USER_PACK_SIZE); \
	ptr = (type*)buffer##type;         \
	ptr->type::type();


template<typename Container>
__inline void stringtok(Container& container, string& in, const char* delimiters = "\t\n", int deep = 0)
{
	size_t len = in.length();
	size_t i = 0;
	int count = 0;
	while (i < len) {
		i = in.find_first_not_of(delimiters, i);
		if (i == string.npos)
			return;

		size_t j = in.find_first_of(delimiters, i);
		count++;
		if (j == string.npos || (deep > 0 && count > deep)) {
			string strTmp = in.substr(i);
			container.push_back(strTmp);
			return;
		} else {
			string strTmp = in.substr(i, j-i);
			container.push_back(strTmp);
		}
		i = j + 1;
	}
}

__inline bool isFileExist(const char* filename)
{
	FILE* file = fopen(filename,"r+b");
	if (file == NULL)
		return false;
	fclose(file);
	return true;
}

// 计算数据中的元素个数
#define count_of(data) sizeof(data)/sizeof(data[0])


#endif

