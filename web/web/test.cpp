//#include <stdio.h>
//#include <stdio.h>
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <errno.h>
//
//#include <string.h>
//int main() {
//	FILE* fp_ =fopen("test_data.csv","w");
//	char path[] = "data.csv";
//	char data[1000][100];
//	//utf - 8格式打开文件
//	FILE* fp = fopen(path, "r");
//	if (fp == NULL) {
//		printf("Error opening file\n");
//		return 1;
//	}
//	int col = 0;
//	for (int i = 0; i < 1000; i++) {
//		if (fgets(data[i], 100, fp) != NULL) {
//			col++;
//		}
//	}
//	for (int i = 0; i < col; i++) {
//		printf("%s", data[i]);
//	}
//	data[1][0] = 'c';
//	fputs(data[1], fp_);
//	/*errno_t eResult;
//	eResult = fopen_s(&fp_, "data.csv", "a+");
//	if (eResult != 0) {
//		exit(-1);
//	}
//	char new_info[100];
//	strcpy(new_info, ",0,0,0,");
//	fputs(new_info, fp_);*/
//	fclose(fp);
//	fclose(fp_);
//}



#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//int main() {
//    char str[] = "a,1,20,100,a,z";
//    const char* numToAdd = "20";
//    const char* target = "100";
//    printf("Before: %s\n", str);
//    addToNumberInString(str, numToAdd, target);
//    printf("After: %s\n", str);
//    return 0;
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//// 比较两个字符串表示的数字大小，返回1表示num1 >= num2，0表示num1 < num2
//int compare(const char* num1, const char* num2) {
//    int len1 = strlen(num1);
//    int len2 = strlen(num2);
//    if (len1 > len2) {
//        return 1;
//    }
//    else if (len1 < len2) {
//        return 0;
//    }
//    else {
//        for (int i = len1 - 1; i >= 0; i--) {
//            if (num1[i] > num2[i]) {
//                return 1;
//            }
//            else if (num1[i] < num2[i]) {
//                return 0;
//            }
//        }
//        return 1;
//    }
//}
//
//// 字符串减法函数
//char* subtract(char* num1, char* num2) {
//    int len1 = strlen(num1);
//    int len2 = strlen(num2);
//    int borrow = 0;
//    char* result = (char*)malloc(len1 + 1);
//    if (result == NULL) {
//        return NULL;
//    }
//    int i = len1 - 1;
//    int j = len2 - 1;
//    int k = len1;
//
//    while (j >= 0) {
//        int sub = (num1[i] - '0') - (num2[j] - '0') - borrow;
//        if (sub < 0) {
//            sub += 10;
//            borrow = 1;
//        }
//        else {
//            borrow = 0;
//        }
//        result[k - 1] = sub + '0';
//        i--;
//        j--;
//        k--;
//    }
//
//    while (i >= 0) {
//        int sub = (num1[i] - '0') - borrow;
//        if (sub < 0) {
//            sub += 10;
//            borrow = 1;
//        }
//        else {
//            borrow = 0;
//        }
//        result[k - 1] = sub + '0';
//        i--;
//        k--;
//    }
//
//    // 去除前导0
//    int start = 0;
//    while (result[start] == '0' && start < len1 - 1) {
//        start++;
//    }
//
//    memmove(result, result + start, len1 - start + 1);
//    result[len1 - start] = '\0';
//    return result;
//}
//
//int main() {
//    char a[] = "21";
//    char b[] = "12";
//    char* c = subtract(a,b);
//    printf("%s", c);
//}
