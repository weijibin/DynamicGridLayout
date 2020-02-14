#ifndef ROLEPLAYDEFINE_H
#define ROLEPLAYDEFINE_H
#include <QString>
#include <QList>
#include <QJsonValue>
#include <QJsonObject>

//IRC数据结构
typedef struct {
    QString  type;              //消息号
    int  status;                // 1分组 2 发题 3 收题
    int      time=90;           //答题时间
    int      gold;
    int courseWareId;           // 课件id
    int packagedId;             // 页面包id
    QString pageIds;            // 页面id
    QString interactId;         // 互动id
    QString role = QStringLiteral("角色B");                  //角色
} IRCRolePlayPar;

typedef struct {
    int bizId;
    bool   isLive;
    QString planId;
    QString classId;
    QString stuCouId;
    QString stuId;
    QString subjectId;
    QString teamId;
    QString subjectName;
    QString getCourseWareUrl;
    QString getGroupTokenUrl;
    QString submitUrl;
    QString imgUrl;
    int     skinType;
    IRCRolePlayPar ircInfo;
} RolePlayBaseInfo;

// 结果页
typedef struct {
    int gold;
    int eval_score; //总分
    int fluence_score;//流畅性
    int accuracy_score;//正确性
} GeneralResult;

// 组信息
typedef struct {
    int            groupId;
    QList<int>     stuIds;
    QList<int>     roleIndexs;

    void clear() {
        groupId = -1;
        stuIds.clear();
        roleIndexs.clear();
    }
} GroupInfo;

// 角色信息
typedef struct {
    QString role;
    QString name;
    QString img_url;
} RoleInfo;

typedef struct {
    QList<RoleInfo>  roleList;
    int    myRoleIndex = -1;     //自己角色的索引
} RolesInfo;


// 每句话的结果
typedef struct {
    QString localFileName;  //读完后的音频文件地址

    int sentenceNum;        //人读的句子顺序排名
    int entranceTime = 0;       //人读句子的时间（单位s）

    int score;              // 整个句子综合得分
    int fluencyScore;       // 整个句子的流畅性得分
    int accurateScore;      // 整个句子的准确性得分
    QJsonValue termScore;   // 每个单词的准确性得分

    QJsonValue allData;     //测评返回的结果
} SpeechResult;

// 对话信息
typedef struct {
    RoleInfo headInfo;          // 头像信息
    QString text;               // 朗读的文本内容
    QString displayText;        // 展示的文本内容，变色使用
    QString audioName;          // audioName
    QString audio_url;          // 朗读的mp3
    int     time;               // 时长

    SpeechResult result;        // 保存评测结果
    int     starNum      = -1;       // 星星数量

    bool    isMyRole     = false;   // 是否是自己的话

    int     p_studId;                 //当前对话对应的stuId 多人点赞时使用

    bool    isNeedPraise = false;

    bool    isAnswered   = false;  // 用来判断回拨
    bool    isSingleRole = true;   // 是否是人机
} SpeechInfo;

typedef struct {
    QList<SpeechInfo>   speechesList;
    bool                is_Eng = true;
    int                 timeCount = 90;
    bool                is_Live = true;
} SpeechesInfo;

#endif // ROLEPLAYDEFINE_H
