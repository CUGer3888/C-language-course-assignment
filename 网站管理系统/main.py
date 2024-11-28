import pandas as pd
import csv
path ="data.csv"
data = pd.read_csv(path,encoding='utf-8')
name_lis = []
user_num = 0
for i in data["name"]:
    name_lis.append(i)
    user_num+=1
pass_word = []
for i in data["password"]:
    pass_word.append(i)
path_1 = "gm_data.csv"
data_1 = pd.read_csv(path_1,encoding='utf-8')
gm_name_lis = []
for i in data_1["name"]:
    gm_name_lis.append(i)
gm_password = []
for i in data_1["password"]:
    gm_password.append(i)
lod_path = "lod.csv"
action_to_score_dir = {}
lod_data = pd.read_csv(lod_path,encoding='utf-8')
action_lis = []
sum = 0
for i in lod_data["action"]:
    if i not in action_lis:
        action_lis.append(i)
    sum+=1
for i in lod_data["action"]:
    if i not in action_to_score_dir:
        col = action_lis.index(i)
        action_to_score_dir[i] = lod_data["score"][col]
while True:
    print("enter num -> 1:load web 2:new_user 3.gm管理员 4:exit")
    num = input()
    if num == "1":
        print("enter name:")
        load_name = input()
        print("enter password:")
        password = input()
        if load_name in name_lis and pass_word[name_lis.index(load_name)] == password:
            print("load success")
            col = name_lis.index(load_name)
            #  1.积分兑换网币2.查看信息  3.网币充值
            while True:
                print("next step: 1.jifen to wangbi   2.detect info 3.add wangbi 4. exit")
                next_num = input()
                if next_num == "1":
                    print("your jifen is: ",data["jifen"][col])
                    print("how many jifen you want to change to wangbi:")
                    jifeng_num = input()
                    if int(jifeng_num) <= data["jifen"][col]:
                        with open(path, 'a', newline='',encoding='utf-8') as f:
                            #修改csv文件中对应行的积分和网币
                            data["jifen"][col] = data["jifen"][col] - int(jifeng_num)
                            data["wangbi"][col] = data["wangbi"][col] + int(jifeng_num)
                            data.to_csv(path, index=False,encoding='utf-8')
                        print("change success")
                    else:
                        print("error")
                elif next_num == "2":
                    #打印对应行的数据
                    print("your info is:\n",data.iloc[col])
                elif next_num == "3":
                    print("how many wangbi you want to add:")
                    wangbi_num = input()
                    with open(path, 'a', newline='',encoding='utf-8') as f:
                        #修改csv文件中对应行的网币
                        data["wangbi"][col] = data["wangbi"][col] + int(wangbi_num)
                        data.to_csv(path, index=False,encoding='utf-8')
                    print("add success")
                elif next_num == "4":
                    break
    elif num == "2":
        print("enter new_name:")
        new_name = input()
        if new_name in name_lis:
            print("name is exist")
        else:
            print("password:")
            password = input()
            with open(path, 'a', newline='',encoding='utf-8') as f:
                #write new_name in this csv file
                writer = csv.writer(f)
                writer.writerow([new_name,1,0,0,password])
                name_lis.append(new_name)
            print("resign success")
    elif num == "3":
        print("enter gm_name:")
        gm_name = input()
        print("enter gm_password:")
        gm_password = input()
        if gm_name in gm_name_lis and gm_password == gm_password[gm_name_lis.index(gm_name)]:
            print("gm load success")
            while True:
                print("next step: 1.修改积分兑换规则 2.读取用户活动文件 3. 累计用户积分 4.exit")
                next_num = input()
                if next_num == "1":
                    print("现在积分规则")
                    print(action_to_score_dir)
                    print("enter new rule:")
                    action = input()
                    if action in action_to_score_dir:
                        print("enter new score:")
                        score = input()
                        action_to_score_dir[action] = score
                        #更新到lod.csv文件中
                        for i in range(sum):
                            lod_data["score"][i] = action_to_score_dir[lod_data["action"][i]]
                        lod_data.to_csv(lod_path, index=False,encoding='utf-8')
                    else:
                        print("error")
                elif next_num == "2":
                    #读取lod文件
                    print("name action  score")
                    for i in range(sum):
                        print(lod_data["name"][i],",",lod_data["action"][i],",",lod_data["score"][i])
                elif next_num == "3":
                    name_dir = {}
                    for i in range(user_num):
                        name_dir[data["name"][i]] = 0
                    for i in range(sum):
                        name_dir[lod_data["name"][i]] += int(lod_data["score"][i])
                    #更新到lod.csv文件中
                    for i in range(user_num):
                        data["jifen"][i] += name_dir[data["name"][i]]
                    data.to_csv(path, index=False,encoding='utf-8')
                elif next_num == "4":
                    break
    elif num == "4":
        break