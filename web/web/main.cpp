
//引用相应的头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <graphics.h>
//使用宏定义，定义数字行和列大小，结构体人名长度，密码长度
#define COL 20
#define ROW 100
#define name_len 30
#define pass_len 30
//定义用户结构体，包括名字，等级，积分，网币，密码
struct user {
	char name[name_len];
	int level;
	int jifen;
	int wangbi;
	char password[pass_len];
};
//定义用户活动结构体，包括id，动作，得分
struct action {
	int id;
	char move[pass_len];
	int score;
};
//定义日志结构体，包括名字，动作，得分
struct lod {
	char name[name_len];
	char action[pass_len];
	int score;
};
void check(int* name_col, struct user* users, char name[name_len], char pass[pass_len], int col) {
	for (int i = 0; i < col; i++) {
		//检查是否名字和密码匹配
		if (!strcmp(users[i].name, name) and !strcmp(users[i].password, pass)) {
			printf("\033[32m load success\033[0m \n");
			*name_col = i;
		}
	}
}
void in(struct user* users, char new_name[name_len], int col, int* a) {
	for (int i = 0; i < col; i++) {
		if (!strcmp(users[i].name, new_name)) {
			*a = 1;
		}
	}
}
//检查名字是否重复
void turn_back(char data[COL][ROW], struct user* users, int col) {
	//将用户信息写入文件
	for (int i = 0; i < col - 1; i++) {
		int a = 0;
		for (int j = 0; j < sizeof(users[i].name); j++) {
			data[i][a++] = users[i].name[a];
			data[i][a] = '\0';
		}
		char level[10];
		char jifen[10];
		char wangbi[10];
		//将用户等级，积分，网币转换为字符串
		sprintf(level, "%d", users[i].level);
		sprintf(jifen, "%d", users[i].jifen);
		sprintf(wangbi, "%d", users[i].wangbi);
		//拼接字符串，写入数组中
		sprintf(data[i], "%s,%s,%s,%s,%s\n", users[i].name, level, jifen, wangbi, users[i].password);
	}
	FILE* fp_ = fopen("data//data.csv", "w");
	//写入开头内容
	char ttt[35] = { "name,level,jifen,wangbi,password\n" };
	fputs(ttt, fp_);
	for (int i = 0; i < col; i++) {
		//将数组中的数据写入文件
		fputs(data[i], fp_);
	}
	fclose(fp_);
}
//将用户活动信息写入文件
void turn_back_lod(char data[COL][ROW], struct lod* lod, int col) {
	for (int i = 0; i < col - 1; i++) {
		//将用户活动信息转换为字符串
		sprintf(data[i], "%s,%s,%d\n", lod[i].name, lod[i].action, lod[i].score);
	}
	FILE* fp_ = fopen("data//lod.csv", "w");
	//写入开头内容
	char ttt[35] = { "name,action,score\n" };
	fputs(ttt, fp_);
	for (int i = 0; i < col; i++) {
		//将数组中的数据写入文件
		fputs(data[i], fp_);
	}
	fclose(fp_);
}
//用户活动信息初始化



//日志信息初始化
void loa_init(struct lod* lod, char data[COL][ROW], int col) {
	for (int i = 1; i < col; i++) {
		lod[i - 1].score = 0;
		int biaoji = 0;
		int douhao[2] = { '0','0' };
		for (int j = 0; j < sizeof(data[i]); j++) {
			if (data[i][j] == ',') {
				biaoji++;
			}
			if (biaoji == 0) {
				douhao[0] = j + 1;
			}
			if (biaoji == 1) {
				douhao[1] = j + 1;
			}
		}
		for (int k = 0; k < douhao[0]; k++) {
			//将名字写入结构体
			lod[i - 1].name[k] = data[i][k];
			lod[i - 1].name[k + 1] = '\0';
		}
		int c = 0;
		for (int k = douhao[0] + 1; k < douhao[1]; k++) {
			//将动作写入结构体
			lod[i - 1].action[c++] = data[i][k];
			lod[i - 1].action[c] = '\0';
		}
		for (int k = douhao[1] + 1; k < strlen(data[i]); k++) {
			//将得分写入结构体
			lod[i - 1].score += (data[i][k] - '0') * pow(10, strlen(data[i]) - k - 1);
		}
	}
}
//活动信息初始化
void act_init(struct action* action, char data[COL][ROW], int col) {
	for (int i = 1; i < col; i++) {
		action[i - 1].score = 0;
		action[i - 1].id = i - 1;
		int biaoji = 0;
		int douhao[2] = { '0','0' };
		for (int j = 0; j < sizeof(data[i]); j++) {
			if (data[i][j] == ',') {
				biaoji++;
			}
			if (biaoji == 0) {
				douhao[0] = j + 1;
			}
			if (biaoji == 1) {
				douhao[1] = j + 1;
			}
		}
		for (int k = 0; k < douhao[0]; k++) {
			//将活动名称写入结构体
			action[i - 1].move[k] = data[i][k];
			action[i - 1].move[k + 1] = '\0';
		}
		for (int k = douhao[1] - 1; k > douhao[0]; k--) {
			//将活动对应得分写入结构体
			action[i - 1].score += (data[i][k] - '0') * pow(10, strlen(data[i]) - k - 4);
		}
	}
}
//将用户信息初始化
void init(struct user* user, char data[COL][ROW], int col) {
	//将用户信息初始化为0
	for (int i = 1; i < col; i++) {
		user[i - 1].jifen = 0;
		user[i - 1].level = 0;
		user[i - 1].wangbi = 0;
	}
	for (int i = 1; i < col; i++) {
		int biaoji = 0;
		int douhao[4] = { '0','0','0','0' };
		for (int j = 0; j < sizeof(data[i]); j++) {
			if (data[i][j] == ',') {
				biaoji++;
			}
			if (biaoji == 0) {
				douhao[0] = j + 1;
			}
			if (biaoji == 1) {
				douhao[1] = j + 1;
			}
			if (biaoji == 2) {
				douhao[2] = j + 1;
			}
			if (biaoji == 3) {
				douhao[3] = j + 1;
			}
		}
		//标记分别定位逗号位置
		for (int k = 0; k < douhao[0]; k++) {
			//将名字写入结构体
			user[i - 1].name[k] = data[i][k];
			user[i - 1].name[k + 1] = '\0';
		}
		for (int k = douhao[1] - 1; k > douhao[0]; k--) {
			//将等级写入结构体
			user[i - 1].level += (data[i][k] - '0') * pow(10, douhao[1] - k - 1);
		}
		for (int k = douhao[2] - 1; k > douhao[1]; k--) {
			//将积分写入结构体
			user[i - 1].jifen += (data[i][k] - '0') * pow(10, douhao[2] - k - 1);
		}
		for (int k = douhao[3] - 1; k > douhao[2]; k--) {
			//将网币写入结构体
			user[i - 1].wangbi += (data[i][k] - '0') * pow(10, douhao[3] - k - 1);
		}
		int a = 0;
		for (int k = douhao[3] + 1; k < strlen(data[i]) - 1; k++) {
			//将密码写入结构体
			user[i - 1].password[a++] = data[i][k];
			user[i - 1].password[a] = '\0';
		}
	}

}
//将管理员信息初始化
void gm_init(struct user* user, char data[COL][ROW], int col) {
	for (int i = 1; i < col; i++) {
		int biaoji = 0;
		int douhao[1] = { '0' };
		for (int j = 0; j < sizeof(data[i]); j++) {
			if (data[i][j] == ',') {
				biaoji++;
			}
			if (biaoji == 0) {
				douhao[0] = j + 1;
				break;
			}
		}
		//标记定位逗号位置
		for (int k = 0; k < douhao[0]; k++) {
			//将名字写入结构体
			user[i - 1].name[k] = data[i][k];
			user[i - 1].name[k + 1] = '\0';
		}
		int a = 0;
		for (int k = douhao[0]; k < strlen(data[i]) - 1; k++) {
			//将密码写入结构体
			user[i - 1].password[a] = data[i][k];
			user[i - 1].password[a + 1] = '\0';
		}
	}
}




void get_col(int* a, FILE* p,char data[COL][ROW]) {
	for (int i = 0; i < COL; i++) {
		if (fgets(data[i], ROW, p) != NULL) {
			*a = i+1;
		}
	}
}
void get_int(int* a) {
	int valid_input = 0;
	do {
		if (scanf("%d", a) != 1) {
			printf("输入无效，请重新输入：");
			while (getchar() != '\n'); // 清空输入缓冲区
		}
		else {
			valid_input = 1;
		}
	} while (!valid_input);
}
int main() {
	//美化界面，使用颜色突出显示
	printf("      * * * * * * * * * * * * * * *\n");
	printf("      * * \033[36m welcome to this web\033[0m  * *\n");
	printf("      * * * * * * * * * * * * * * *\n");
	char data[COL][ROW];
	//将用户信息初始化
	FILE* fp = fopen("data//data.csv", "r");
	int col = 0;
	get_col(&col, fp, data);
	struct user* users = (struct user*)malloc((col + 10) * sizeof(struct user));
	init(users, data, col);
	fclose(fp);
	//将管理员信息初始化
	char gm_data[COL][ROW];
	FILE* fp_ = fopen("data//gm_data.csv", "r");
	int col_ = 0;
	get_col(&col_, fp_, gm_data);
	struct user* gm_users = (struct user*)malloc(col_ * sizeof(struct user));
	gm_init(gm_users, gm_data, col_);
	fclose(fp_);
	//将用户活动规则初始化
	char action[COL][ROW] = { '\0' };
	FILE* fp__ = fopen("data//turn_rule.csv", "r");
	int col__ = 0;
	get_col(&col__, fp__, action);
	struct action* turn_rules = (struct action*)malloc(col__ * sizeof(struct action));
	act_init(turn_rules, action, col__);
	fclose(fp__);

	//定义日志信息数组
	char lod_data[COL][ROW];
	//读取文件信息，并记录文件行数
	FILE* fp_1 = fopen("data//lod.csv", "r");
	int lod_col = 0;
	while (fscanf(fp_1, "%s", lod_data[lod_col]) != EOF) {
		lod_col++;
	}
	//将日志信息初始化
	struct lod* lod = (struct lod*)malloc(lod_col * sizeof(struct lod));
	loa_init(lod, lod_data, lod_col);
	fclose(fp_1);

	//循环开始
	while (1) {
		//打印菜单
		printf("\033[31m-----------------------------------------\033[0m \n");
		printf("      * * * * * * * * * * * * * * *\n");
		printf("      * *   \033[34m enter num \033[0m         * *\n");
		printf("      * * * * * * * * * * * * * * *\n");
		printf("      * *   \033[34m1:load web \033[0m         * *\n");
		printf("      * *   \033[34m2:new_user \033[0m         * *\n");
		printf("      * *   \033[34m3:gm管理员 \033[0m         * *\n");
		printf("      * *   \033[34m4:exit \033[0m             * *\n");
		printf("      * * * * * * * * * * * * * * *\n");
		printf("\033[31m-----------------------------------------\033[0m \nenter number ---->   ");

		int number;
		get_int(&number);
		//根据输入的数字执行相应的操作
		if (number == 1) {
			printf("---> enter your name:(\033[31m max size: seven\033[0m)   ");
			char name[name_len];
			char pass[pass_len];
			scanf("%s", &name);
			printf("---> enter password:(\033[31m max size: fifteen \033[0m) ");
			scanf("%s", &pass);
			int name_col = -1;
			check(&name_col, users, name, pass, col - 1);
			if (name_col < 0) {
				printf("----\033[31m name or password error!\033[0m ----\n");
			}
			//如果用户存在，则进入下一步
			while (name_col >= 0) {
				//打印下一步菜单
				printf("\033[31m-----------------------------------------\033[0m \n");
				printf("      * * * * * * * * * * * * * * *\n");
				printf("      * *   \033[34m next step \033[0m         * *\n");
				printf("      * * * * * * * * * * * * * * *\n");
				printf("      * *   \033[34m 1.jifen to wangbi \033[0m * *\n");
				printf("      * *   \033[34m 2.detect info \033[0m     * *\n");
				printf("      * *   \033[34m 3.add wangbi \033[0m      * *\n");
				printf("      * *   \033[34m 4. exit \033[0m           * *\n");
				printf("      * * * * * * * * * * * * * * *\n");
				printf("\033[31m-----------------------------------------\033[0m \n    --->");
				int next_num;
				get_int(&next_num);
				if (next_num == 1) {
					//积分兑换网币
					printf("--- your jifen is:\033[34m %d \033[0m ---\n", users[name_col].jifen);
					printf("--- how many jifen you want to change to wangbi: --->");
					int jifen_to_wangbi;
					get_int(&jifen_to_wangbi);
					if (jifen_to_wangbi < users[name_col].jifen) {
						users[name_col].jifen -= jifen_to_wangbi;
						users[name_col].wangbi += jifen_to_wangbi;
						printf("\033[32m success\033[0m\n");
					}
					else {
						printf("\033[31m积分不足\033[0m\n");
					}
				}
				if (next_num == 2) {
					//输出用户信息
					printf("--- your infomation ---\n");
					printf("--- name:\033[34m   %s \033[0m--- \n", users[name_col].name);
					printf("--- dengji:\033[34m %d \033[0m--- \n", users[name_col].level);
					printf("--- jifen:\033[34m  %d  \033[0m--- \n", users[name_col].jifen);
					printf("--- wangbi:\033[34m %d \033[0m--- \n", users[name_col].wangbi);
				}
				if (next_num == 3) {
					//网币充值
					printf("--- how many wangbi you want to add : --->");
					int wangbi_num;
					get_int(&wangbi_num);
					users[name_col].wangbi += wangbi_num;
				}
				if (next_num == 4) {
					//退出
					printf("exit\n");
					break;
				}
			}
		}
		if (number == 2) {
			//注册新用户
			printf("--- enter new_name : --->");
			char new_name[name_len];
			scanf("%s", &new_name);
			int aaa = 0;
			//检查用户名是否已存在
			in(users, new_name, col, &aaa);
			if (aaa == 1) {
				printf("--- \033[31m name is exist\033[0m ---\n");
			}
			else {
				//如果用户名不存在，则注册新用户
				int a = 0;
				for (int i = 0; i < name_len; i++) {
					if (new_name[i] == '\0') {
						break;
					}
					a++;
				}
				printf("--- password : --->");
				char password[name_len];
				scanf("%s", password);
				int b = 0;
				for (int i = 0; i < pass_len; i++) {
					if (password[i] == '\0')break;
					b++;
				}
				col--;
				for (int i = 0; i < a; i++) {
					users[col].name[i] = new_name[i];
					users[col].name[i + 1] = '\0';
				}
				for (int i = 0; i < b; i++) {
					users[col].password[i] = password[i];
					users[col].password[i + 1] = '\0';
				}
				users[col].level = 1;
				users[col].jifen = 0;
				users[col].wangbi = 0;
				printf("\033[32m resign success\033[0m \n");
				col += 2;
			}
		}
		if (number == 3) {
			//管理员登录
			printf("--- enter gm_name: --->");
			char gm_name[name_len];
			scanf("%s", gm_name);
			printf("--- enter gm_password: --->");
			char gm_password[pass_len];
			scanf("%s", gm_password);
			//检查管理员用户名和密码是否正确
			int gm_name_col = -1;
			check(&gm_name_col, gm_users, gm_name, gm_password, col_ - 1);
			if (gm_name_col < 0) {
				printf("\033[31m name or password error!\033[0m\n");
			}
			while (gm_name_col >= 0) {
				//管理员登录成功，进入管理员界面
				printf("\033[31m-----------------------------------------\033[0m \n");
				printf("      * * * * * * * * * * * * * * *\n");
				printf("      * *   \033[34m next step: \033[0m        * *\n");
				printf("      * * * * * * * * * * * * * * *\n");
				printf("      * *   \033[34m 1.修改积分兑换规则 \033[0m* *\n");
				printf("      * *   \033[34m 2.读取用户活动文件 \033[0m* *\n");
				printf("      * *   \033[34m 3.累计用户积分 \033[0m    * *\n");
				printf("      * *   \033[34m 4.exit \033[0m            * *\n");
				printf("      * * * * * * * * * * * * * * *\n");
				printf("\033[31m-----------------------------------------\033[0m \n");
				int next_number;
				get_int(&next_number);
				if (next_number == 1) {
					//修改积分兑换规则
					printf("--- 现在积分规则 ---\n");
					for (int i = 0; i < col__ - 1; i++) {
						printf("* %d act:%s score: %d *\n", turn_rules[i].id, turn_rules[i].move, turn_rules[i].score);
					}
					printf("--- enter new rule_id: --->");
					int new_rule_id;
					get_int(&new_rule_id);
					printf("--- enter new score: --->");
					int new_score;
					get_int(&new_score);
					turn_rules[new_rule_id].score = new_score;
					for (int i = 0; i < lod_col; i++) {
						if (strcmp(turn_rules[new_rule_id].move, lod[i].action) == 0) {
							lod[i].score = new_score;
						}
					}
				}
				if (next_number == 2) {
					//输出用户活动文件
					printf("--- 用户活动文件 ---\n");
					for (int i = 0; i < lod_col - 1; i++) {
						printf("* name:%s  act:%s  score:%d *\n", lod[i].name, lod[i].action, lod[i].score);
					}
				}
				if (next_number == 3) {
					//累计用户积分
					for (int i = 0; i < lod_col; i++) {
						for (int j = 0; j < col; j++) {
							if (strcmp(users[j].name, lod[i].name) == 0) {
								users[j].jifen += lod[i].score;
							}
						}
					}
					printf("--- success ---\n");
				}
				if (next_number == 4) {
					//退出管理员界面
					printf("exit\n");
					break;
				}
			}
		}
		if (number == 4) {
			//退出登录,并保存用户数据
			char new_data[COL][ROW] = { '\0' };
			char new_data_lod[COL][ROW] = { '\0' };
			turn_back(new_data, users, col);
			turn_back_lod(new_data_lod, lod, lod_col);
			printf("exit!");
			break;
		}
	}
	return 0;
}
