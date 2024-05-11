typedef void (*student_show_callback_t)(void *);

typedef struct student_t {
    char *name;
    int number;
    int phone;
    student_show_callback_t show;
} student_t;

int student_init(student_t *stu, const char *name, int number, int phone, student_show_callback_t show);