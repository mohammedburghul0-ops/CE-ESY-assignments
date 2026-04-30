#include <stdio.h>
#include <string.h>

// تحديد السعة القصوى للمخزن
#define BUFFER_MAX 22 

// تعريف بنية المخزن الدائري بأسماء مختلفة
typedef struct {
    char items[BUFFER_MAX];
    int read_pos;    // مكان سحب البيانات
    int write_pos;   // مكان إدخال البيانات
    int current_len; // لتتبع عدد العناصر الحالية
} RingBuffer;

// دالة تصفير مؤشرات المخزن
void initialize_buffer(RingBuffer *rb) {
    rb->read_pos = 0;
    rb->write_pos = 0;
    rb->current_len = 0;
}

// فحص هل المخزن ممتلئ
int is_buffer_full(RingBuffer *rb) {
    return (rb->current_len == BUFFER_MAX);
}

// فحص هل المخزن فارغ
int is_buffer_empty(RingBuffer *rb) {
    return (rb->current_len == 0);
}

// إضافة عنصر جديد
void insert_data(RingBuffer *rb, char val) {
    if (is_buffer_full(rb)) {
        printf("Error: Overflow! Cannot insert '%c'\n", val);
        return;
    }
    rb->items[rb->write_pos] = val;
    rb->write_pos = (rb->write_pos + 1) % BUFFER_MAX;  
    rb->current_len++;
}

// سحب عنصر من المخزن
char extract_data(RingBuffer *rb) {
    if (is_buffer_empty(rb)) {
        printf("Error: Underflow! Buffer is empty.\n");
        return '\0';
    }
    char val = rb->items[rb->read_pos];
    rb->read_pos = (rb->read_pos + 1) % BUFFER_MAX;
    rb->current_len--;
    return val;
}

int main() {
    RingBuffer myBuffer;
    initialize_buffer(&myBuffer);

    char input_string[50];
    char appended_text[] = "CE-ESY";

    // استقبال بيانات المستخدم
    printf("Please type your name: ");
    scanf("%s", input_string);

    // دمج السلسلة المطلوبة
    strcat(input_string, appended_text);
    printf("Final string to process: %s\n", input_string);
    printf("--- Testing with Capacity = %d ---\n", BUFFER_MAX);

    // كتابة محارف السلسلة ضمن المخزن
    for (int j = 0; input_string[j] != '\0'; j++) {
        insert_data(&myBuffer, input_string[j]);
    }

    // استخراج المحارف وطباعتها
    printf("Output from buffer: ");
    while (!is_buffer_empty(&myBuffer)) {
        printf("%c", extract_data(&myBuffer));
    }

    // اختبار حالة المخزن النهائية
    if (is_buffer_empty(&myBuffer)) {
        printf("\nStatus: Buffer successfully emptied.\n");
    }
    
    // تجربة قراءة إضافية لاختبار الفراغ (Underflow)
    printf("Attempting to read again: ");
    extract_data(&myBuffer);

    return 0;
}