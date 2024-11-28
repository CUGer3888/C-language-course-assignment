
//������Ӧ��ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <graphics.h>
//ʹ�ú궨�壬���������к��д�С���ṹ���������ȣ����볤��
#define COL 20
#define ROW 100
#define name_len 7
#define pass_len 15
//�����û��ṹ�壬�������֣��ȼ������֣����ң�����
struct user {
	char name[name_len];
	int level;
	int jifen;
	int wangbi;
	char password[pass_len];
};
//�����û���ṹ�壬����id���������÷�
struct action {
	int id;
	char move[pass_len];
	int score;
};
//������־�ṹ�壬�������֣��������÷�
struct lod {
	char name[name_len];
	char action[pass_len];
	int score;
};
void check(int* name_col, struct user* users, char name[name_len], char pass[pass_len], int col) {
	for (int i = 0; i < col; i++) {
		//����Ƿ����ֺ�����ƥ��
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
//��������Ƿ��ظ�
void turn_back(char data[COL][ROW], struct user* users, int col) {
	//���û���Ϣд���ļ�
	for (int i = 0; i < col - 1; i++) {
		int a = 0;
		for (int j = 0; j < sizeof(users[i].name); j++) {
			data[i][a++] = users[i].name[a];
			data[i][a] = '\0';
		}
		char level[10];
		char jifen[10];
		char wangbi[10];
		//���û��ȼ������֣�����ת��Ϊ�ַ���
		sprintf(level, "%d", users[i].level);
		sprintf(jifen, "%d", users[i].jifen);
		sprintf(wangbi, "%d", users[i].wangbi);
		//ƴ���ַ�����д��������
		sprintf(data[i], "%s,%s,%s,%s,%s\n", users[i].name, level, jifen, wangbi, users[i].password);
	}
	FILE* fp_ = fopen("data//data.csv", "w");
	//д�뿪ͷ����
	char ttt[35] = { "name,level,jifen,wangbi,password\n" };
	fputs(ttt, fp_);
	for (int i = 0; i < col; i++) {
		//�������е�����д���ļ�
		fputs(data[i], fp_);
	}
	fclose(fp_);
}
//���û����Ϣд���ļ�
void turn_back_lod(char data[COL][ROW], struct lod* lod, int col) {
	for (int i = 0; i < col - 1; i++) {
		//���û����Ϣת��Ϊ�ַ���
		sprintf(data[i], "%s,%s,%d\n", lod[i].name, lod[i].action, lod[i].score);
	}
	FILE* fp_ = fopen("data//lod.csv", "w");
	//д�뿪ͷ����
	char ttt[35] = { "name,action,score\n" };
	fputs(ttt, fp_);
	for (int i = 0; i < col; i++) {
		//�������е�����д���ļ�
		fputs(data[i], fp_);
	}
	fclose(fp_);
}
//�û����Ϣ��ʼ��
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
			//������д��ṹ��
			lod[i - 1].name[k] = data[i][k];
			lod[i - 1].name[k + 1] = '\0';
		}
		int c = 0;
		for (int k = douhao[0] + 1; k < douhao[1]; k++) {
			//������д��ṹ��
			lod[i - 1].action[c++] = data[i][k];
			lod[i - 1].action[c] = '\0';
		}
		for (int k = douhao[1] + 1; k < strlen(data[i]); k++) {
			//���÷�д��ṹ��
			lod[i - 1].score += (data[i][k] - '0') * pow(10, strlen(data[i]) - k - 1);
		}
	}
}
//���Ϣ��ʼ��
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
			//�������д��ṹ��
			action[i - 1].move[k] = data[i][k];
			action[i - 1].move[k + 1] = '\0';
		}
		for (int k = douhao[1] - 1; k > douhao[0]; k--) {
			//�����Ӧ�÷�д��ṹ��
			action[i - 1].score += (data[i][k] - '0') * pow(10, strlen(data[i]) - k - 4);
		}
	}
}
//���û���Ϣ��ʼ��
void init(struct user* user, char data[COL][ROW], int col) {
	//���û���Ϣ��ʼ��Ϊ0
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
		//��Ƿֱ�λ����λ��
		for (int k = 0; k < douhao[0]; k++) {
			//������д��ṹ��
			user[i - 1].name[k] = data[i][k];
			user[i - 1].name[k + 1] = '\0';
		}
		for (int k = douhao[1] - 1; k > douhao[0]; k--) {
			//���ȼ�д��ṹ��
			user[i - 1].level += (data[i][k] - '0') * pow(10, douhao[1] - k - 1);
		}
		for (int k = douhao[2] - 1; k > douhao[1]; k--) {
			//������д��ṹ��
			user[i - 1].jifen += (data[i][k] - '0') * pow(10, douhao[2] - k - 1);
		}
		for (int k = douhao[3] - 1; k > douhao[2]; k--) {
			//������д��ṹ��
			user[i - 1].wangbi += (data[i][k] - '0') * pow(10, douhao[3] - k - 1);
		}
		int a = 0;
		for (int k = douhao[3] + 1; k < strlen(data[i]) - 1; k++) {
			//������д��ṹ��
			user[i - 1].password[a++] = data[i][k];
			user[i - 1].password[a] = '\0';
		}
	}

}
//������Ա��Ϣ��ʼ��
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
		//��Ƕ�λ����λ��
		for (int k = 0; k < douhao[0]; k++) {
			//������д��ṹ��
			user[i - 1].name[k] = data[i][k];
			user[i - 1].name[k + 1] = '\0';
		}
		int a = 0;
		for (int k = douhao[0]; k < strlen(data[i]) - 1; k++) {
			//������д��ṹ��
			user[i - 1].password[a] = data[i][k];
			user[i - 1].password[a + 1] = '\0';
		}
	}
}


int main() {
	//�������棬ʹ����ɫͻ����ʾ
	printf("      * * * * * * * * * * * * * * *\n");
	printf("      * * * \033[36m welcome to this web\033[0m * *\n");
	printf("      * * * * * * * * * * * * * * *\n");
	//�����û���Ϣ����
	char data[COL][ROW];
	//��ȡ�ļ���Ϣ������¼�ļ�����
	FILE* fp = fopen("data//data.csv", "r");
	int col = 0;
	for (int i = 0; i < COL; i++) {
		if (fgets(data[i], ROW, fp) != NULL) {
			col++;
		}
	}
	//���û���Ϣ��ʼ��
	struct user* users = (struct user*)malloc((col + 10) * sizeof(struct user));
	init(users, data, col);
	fclose(fp);
	//�������Ա��Ϣ����
	char gm_data[COL][ROW];
	//��ȡ�ļ���Ϣ������¼�ļ�����
	FILE* fp_ = fopen("data//gm_data.csv", "r");
	int col_ = 0;
	for (int i = 0; i < COL; i++) {
		if (fgets(gm_data[i], ROW, fp_) != NULL) {
			col_++;
		}
	}
	//������Ա��Ϣ��ʼ��
	struct user* gm_users = (struct user*)malloc(col_ * sizeof(struct user));
	gm_init(gm_users, gm_data, col_);
	fclose(fp_);
	//������Ϣ����
	char action[COL][ROW] = { '\0' };
	//��ȡ�ļ���Ϣ������¼�ļ�����
	FILE* fp__ = fopen("data//turn_rule.csv", "r");
	int col__ = 0;
	for (int i = 0; i < COL; i++) {
		if (fgets(action[i], ROW, fp__) != NULL) {
			col__++;
		}
	}
	//�����Ϣ��ʼ��
	struct action* turn_rules = (struct action*)malloc(col__ * sizeof(struct action));
	act_init(turn_rules, action, col__);
	fclose(fp__);
	//������־��Ϣ����
	char lod_data[COL][ROW];
	//��ȡ�ļ���Ϣ������¼�ļ�����
	FILE* fp_1 = fopen("data//lod.csv", "r");
	int lod_col = 0;
	while (fscanf(fp_1, "%s", lod_data[lod_col]) != EOF) {
		lod_col++;
	}
	//����־��Ϣ��ʼ��
	struct lod* lod = (struct lod*)malloc(lod_col * sizeof(struct lod));
	fclose(fp_1);
	loa_init(lod, lod_data, lod_col);
	//ѭ����ʼ
	while (1) {
		//��ӡ�˵�
		printf("\033[31m-----------------------------------------\033[0m \n");
		printf("      * * * * * * * * * * * * * * *\n");
		printf("      * * * \033[34m enter num \033[0m * * * * * * * \n");
		printf("      * * * * * * * * * * * * * * *\n");
		printf("      * * * \033[34m1:load web \033[0m* * * * * *\n");
		printf("      * * * \033[34m2:new_user \033[0m* * * * * *\n");
		printf("      * * * \033[34m3:gm����Ա \033[0m* * * * * *\n");
		printf("      * * * \033[34m4:exit \033[0m * * * * * * * *\n");
		printf("      * * * * * * * * * * * * * * *\n");
		printf("\033[31m-----------------------------------------\033[0m \nenter number ---->   ");

		int number;
		int valid_input = 0; // ��������Ƿ���Ч
		//ʹ��do-whileѭ��ȷ��������Ч
		do {
			if (scanf("%d", &number) == 1) {
				valid_input = 1; // ������Ч
			}
			else {
				printf("����������һ������\n");
				// ������뻺�����е���Ч�ַ�
				while (getchar() != '\n');
			}
		} while (!valid_input);
		//�������������ִ����Ӧ�Ĳ���
		if (number == 1) {
			printf("---> enter your name:(\033[31m max size: seven\033[0m)   ");
			char name[name_len];
			char pass[pass_len];
			//try��ֹ����name_len
			try {
				scanf("%s", &name);
			}
			catch (const char* msg) {
				printf("your enter name lenth is too long\n");
			}

			printf("---> enter password:(\033[31m max size: fifteen \033[0m) ");
			try {
				scanf("%s", &pass);
			}
			catch (const char* msg) {
				printf("your enter password lenth is too long\n");
			}
			int name_col = -1;
			check(&name_col, users, name, pass, col - 1);
			if (name_col < 0) {
				printf("----\033[31m name or password error!\033[0m ----\n");
			}
			//����û����ڣ��������һ��
			while (name_col >= 0) {
				//��ӡ��һ���˵�
				printf("\033[31m-----------------------------------------\033[0m \n");
				printf("      * * * * * * * * * * * * * * *\n");
				printf("      * * * \033[34m next step \033[0m * * * * * * * *\n");
				printf("      * * * * * * * * * * * * * * *\n");
				printf("      * * * \033[34m 1.jifen to wangbi \033[0m * * * *\n");
				printf("      * * * \033[34m 2.detect info \033[0m* * * * * * *\n");
				printf("      * * * \033[34m 3.add wangbi \033[0m* * * * * * *\n");
				printf("      * * * \033[34m 4. exit \033[0m * * * * * * * * *\n");
				printf("      * * * * * * * * * * * * * * *\n");
				printf("\033[31m-----------------------------------------\033[0m \n    --->");
				int next_num;
				int valid_input = 0; // ��������Ƿ���Ч
				//ʹ��do-whileѭ��ȷ��������Ч
				do {
					if (scanf("%d", &next_num) == 1) {
						valid_input = 1; // ������Ч
					}
					else {
						printf("����������һ������\n");
						// ������뻺�����е���Ч�ַ�
						while (getchar() != '\n');
					}
				} while (!valid_input);
				if (next_num == 1) {
					//���ֶһ�����
					printf("--- your jifen is:\033[34m %d \033[0m ---\n", users[name_col].jifen);
					printf("--- how many jifen you want to change to wangbi: --->");
					int jifen_to_wangbi;
					scanf("%d", &jifen_to_wangbi);
					if (jifen_to_wangbi < users[name_col].jifen) {
						users[name_col].jifen -= jifen_to_wangbi;
						users[name_col].wangbi += jifen_to_wangbi;
						printf("\033[32m success\033[0m\n");
					}
					else {
						printf("\033[31m���ֲ���\033[0m\n");
					}
				}
				if (next_num == 2) {
					//����û���Ϣ
					printf("--- your infomation ---\n");
					printf("--- name:\033[34m   %s \033[0m--- \n", users[name_col].name);
					printf("--- dengji:\033[34m %d \033[0m--- \n", users[name_col].level);
					printf("--- jifen:\033[34m  %d  \033[0m--- \n", users[name_col].jifen);
					printf("--- wangbi:\033[34m %d \033[0m--- \n", users[name_col].wangbi);
				}
				if (next_num == 3) {
					//���ҳ�ֵ
					printf("--- how many wangbi you want to add : --->");
					int wangbi_num;
					scanf("%d", &wangbi_num);
					users[name_col].wangbi += wangbi_num;
				}
				if (next_num == 4) {
					//�˳�
					printf("exit\n");
					break;
				}
			}
		}
		if (number == 2) {
			//ע�����û�
			printf("--- enter new_name : --->");
			char new_name[name_len];
			//try-catch��ֹ����name_len
			try {
				scanf("%s", &new_name);
			}
			catch (const char* msg) {
				printf("your enter name lenth is too long\n");
			}
			int aaa = 0;
			//����û����Ƿ��Ѵ���
			in(users, new_name, col, &aaa);
			if (aaa == 1) {
				printf("--- \033[31m name is exist\033[0m ---\n");
			}
			else {
				//����û��������ڣ���ע�����û�
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
					users[col].name[i += 1] = '\0';
				}
				for (int i = 0; i < b; i++) {
					users[col].password[i] = password[i];
					users[col].password[i += 1] = '\0';
				}
				users[col].level = 1;
				users[col].jifen = 0;
				users[col].wangbi = 0;
				printf("\033[32m resign success\033[0m \n");
				col += 2;
			}
		}
		if (number == 3) {
			//����Ա��¼
			printf("--- enter gm_name: --->");
			char gm_name[name_len];
			//try-catch��ֹ����name_len
			try {
				scanf("%s", gm_name);
			}
			catch (const char* msg) {
				printf("your enter name lenth is too long\n");
			}
			printf("--- enter gm_password: --->");
			char gm_password[pass_len];
			//try-catch��ֹ����pass_len
			try {
				scanf("%s", gm_password);
			}
			catch (const char* msg) {
				printf("your enter password lenth is too long\n");
			}
			//������Ա�û����������Ƿ���ȷ
			int gm_name_col = -1;
			check(&gm_name_col, gm_users, gm_name, gm_password, col_ - 1);
			if (gm_name_col < 0) {
				printf("\033[31m name or password error!\033[0m\n");
			}
			while (gm_name_col >= 0) {
				//����Ա��¼�ɹ����������Ա����
				printf("\033[31m-----------------------------------------\033[0m \n");
				printf("      * * * * * * * * * * * * * * *\n");
				printf("      * * * \033[34m next step: \033[0m * * * * * * * *\n");
				printf("      * * * * * * * * * * * * * * *\n");
				printf("      * * * \033[34m 1.�޸Ļ��ֶһ����� \033[0m * * * *\n");
				printf("      * * * \033[34m 2.��ȡ�û���ļ� \033[0m* * * * * * *\n");
				printf("      * * * \033[34m 3. �ۼ��û����� \033[0m* * * * * * *\n");
				printf("      * * * \033[34m 4. exit \033[0m * * * * * * * * *\n");
				printf("      * * * * * * * * * * * * * * *\n");
				printf("\033[31m-----------------------------------------\033[0m \n");
				int next_number;
				int valid_input = 0; // ��������Ƿ���Ч
				//ʹ��do-whileѭ��ȷ��������Ч
				do {
					if (scanf("%d", &next_number) == 1) {
						valid_input = 1; // ������Ч
					}
					else {
						printf("����������һ������\n");
						// ������뻺�����е���Ч�ַ�
						while (getchar() != '\n');
					}
				} while (!valid_input);
				if (next_number == 1) {
					//�޸Ļ��ֶһ�����
					printf("--- ���ڻ��ֹ��� ---\n");
					for (int i = 0; i < col__ - 1; i++) {
						printf("* %d act:%s score: %d *\n", turn_rules[i].id, turn_rules[i].move, turn_rules[i].score);
					}
					printf("--- enter new rule_id: --->");
					int new_rule_id;
					scanf("%d", &new_rule_id);
					printf("--- enter new score: --->");
					int new_score;
					scanf("%d", &new_score);
					turn_rules[new_rule_id].score = new_score;
					for (int i = 0; i < lod_col; i++) {
						if (strcmp(turn_rules[new_rule_id].move, lod[i].action) == 0) {
							lod[i].score = new_score;
						}
					}
				}
				if (next_number == 2) {
					//����û���ļ�
					printf("--- �û���ļ� ---\n");
					for (int i = 0; i < lod_col - 1; i++) {
						printf("* name:%s  act:%s  score:%d *\n", lod[i].name, lod[i].action, lod[i].score);
					}
				}
				if (next_number == 3) {
					//�ۼ��û�����
					for (int i = 0; i < lod_col; i++) {
						for (int j = 0; j < col; j++) {
							if (strcmp(users[j].name, lod[i].name) == 0) {
								users[j].jifen += lod[i].score;
							}
						}
					}
				}
				if (next_number == 4) {
					//�˳�����Ա����
					printf("exit\n");
					break;
				}
			}
		}
		if (number == 4) {
			//�˳���¼,�������û�����
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