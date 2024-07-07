/**
实现函数，给定英文段落，返回出现次数最多的单词，如果次数相等，则都显示
比如

输入： hello cvte,hello
输出：hello

输入：a apple, the apple, a big banana
输出：a apple
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000  // 假设最多处理1000个单词

 // 哈希表节点定义
typedef struct {
    char word[100];  // 单词最大长度为100
    int count;       // 单词出现次数
} word_count_t;

// 哈希表结构定义
typedef struct {
    word_count_t data[MAX_WORDS];  // 哈希表数据存储
    int size;                   // 当前哈希表中的单词数量
} hash_table_t;

// 哈希函数，计算单词的哈希值
unsigned int hash_function(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % MAX_WORDS;
}

// 初始化哈希表
void hash_table_init(hash_table_t *table)
{
    table->size = 0;
    for (int i = 0; i < MAX_WORDS; i++) {
        table->data[i].word[0] = '\0';  // 将单词设为空字符串表示该位置为空
        table->data[i].count = 0;
    }
}

// 插入单词到哈希表中，如果已存在则增加计数
void insert_word(hash_table_t *table, const char *word)
{
    unsigned int index = hash_function(word);

#if 1
    // 检查是否已经存在该单词
    for (int i = 0; i < table->size; i++) {
        if (strcmp(table->data[i].word, word) == 0) {
            table->data[i].count++;
            return;
        }
    }

    // 如果不存在，则插入新单词
    strcpy(table->data[table->size].word, word);
    table->data[table->size].count = 1;
    table->size++;
#endif

}

// 从英文段落中解析出单词并插入哈希表
void parse_and_count_words(hash_table_t *table, const char *paragraph)
{
    char word[100];  // 假设单词最大长度为100
    int i = 0, j = 0;

    while (paragraph[i]) {
        if (isalnum(paragraph[i])) {  // 判断是否是字母或数字
            word[j++] = tolower(paragraph[i]);  // 转换为小写字母存储
        } else if (j > 0) {  // 遇到非字母或数字字符，结束一个单词的识别
            word[j] = '\0';  // 添加字符串结尾标志
            insert_word(table, word);  // 插入单词到哈希表
            j = 0;  // 重置单词缓冲区索引
        }
        i++;
    }

    // 处理最后一个单词
    if (j > 0) {
        word[j] = '\0';
        insert_word(table, word);
    }
}

// 找出出现次数最多的单词或者所有出现次数最多的单词
void find_most_frequent_words(const char *paragraph)
{
    hash_table_t table;
    hash_table_init(&table);

    // 解析并统计单词
    parse_and_count_words(&table, paragraph);

    // 找出最大出现次数
    int maxCount = 0;
    for (int i = 0; i < table.size; i++) {
        if ((table.data[i].count > maxCount) && (table.data[i].word[0] != '\0')) {
            maxCount = table.data[i].count;
        }
    }

    // 输出所有出现次数最大的单词
    printf("出现次数最多的单词有：\n");
    for (int i = 0; i < table.size; i++) {
        if (table.data[i].word[0] != '\0') {
            // if (table.data[i].count == maxCount) {
            printf("%s, %d次\n", table.data[i].word, table.data[i].count);
            // }
        }

    }
}

// 主函数
int main()
{
    char paragraph[1000] = "asd asd dasdas asdasdqwewqe ZDasd sdqwaed asd asd wess s ss s sss";

    // 输入英文段落
    // printf("请输入英文段落：\n");
    // fgets(paragraph, sizeof(paragraph), stdin);



    // 调用函数找出出现次数最多的单词
    find_most_frequent_words(paragraph);

    return 0;
}
