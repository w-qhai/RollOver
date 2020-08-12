#include "ConfigConvert.h"

/// <summary>
/// 读取一个配置项，并且返回KEY对应的VALUE
/// </summary>
/// <param name="configPath">配置项位置</param>
/// <param name="configKey">寻找的KEY</param>
/// <returns></returns>

std::string ConfigConvert::getConfig(const char* configPath, const char* configKey) {

	// 打开一个文件
	std::fstream fin(configPath, std::ios::in);
	std::string szLine("");
	// 如果打开文件失败（可能是不存在也可能是其他软件正在读取写入）
	if (!fin) {
		return "";
	}

	// 如果打开文件成功

	while (std::getline(fin, szLine)) {

		// 注释符号 # 在此之后的所有字符串将被忽略

		int iCommentPos = szLine.find("#");

		if (iCommentPos != szLine.npos) {

			// 查询到有 # 注释符号，提取前面内容

			szLine = szLine.substr(0, iCommentPos);

		}

		// 搜寻是否有分隔符 = 

		int iDelimiterPos = szLine.find("=");

		std::string currentKey = szLine.substr(0, iDelimiterPos);

		if (iDelimiterPos != szLine.npos) {

			//寻找到分隔符 = 并且和需要寻找的key相同，则提取key对应的Value

			if (currentKey == configKey) {

				// 获取当前行的长度，定位到最后一个字符的后面

				int iLineLength = szLine.length();

				// 获取应该取多少个字符

				int iContentLength = iLineLength - iDelimiterPos - 1;

				// 从第几个开始取

				int iBef = iDelimiterPos + 1;

				fin.close();

				// 检测 iBef(需要取的第一个字符) 是否在 iLineLength(需要取的最后一个字符)的前面

				if (iBef < iLineLength) {

					// 如果有内容，则取出来

					szLine = szLine.substr(iBef, iContentLength);

					return szLine;

				}
				else {

					// 如果没有内容，则返回空值

					return "";

				}

			}

		}

	}

	fin.close();

	return "";
}


/// <summary>
///  添加一个配置项到指定文件中，若没有此文件将自动创建
/// </summary>
/// <param name="configPath">文件路径</param>
/// <param name="configKey">配置项KEY</param>
/// <param name="configValue">配置项VALUE</param>
/// <param name="configComment">配置项注释(为空则不写入注释)</param>
/// <returns></returns>

bool ConfigConvert::addConfig(const char* configPath, const char* configKey, const char* configValue, const char* configComment) {

	// 打开一个文件
	std::fstream fout(configPath, std::ios::app);
	// 如果打开文件失败（可能是不存在也可能是其他软件正在读取写入）
	if (!fout) {
		return false;
	}

	// 如果输入的注释不为空，则写入注释，否则跳过

	if (configComment != "")
		fout << "# " << configComment << std::endl;

	fout << configKey << "=" << configValue << std::endl;

	fout.close();

	return true;
}