#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//상품 정보 구조체체
struct product {
    char name[20];
    int price;
};

// 고객 정보 구조체
struct client {
    char name[20]; // 고객명
    char adress[100];  // 주소
    char phone[20]; // 전화번호
};

// 주문 정보 구조체
struct order {
    int id;
    char p_name[20]; // 상품명
    char cli_name[20]; // 고객 이름
    char date[20]; // 주문 날짜
    int quantity; // 수량
};

//목록
struct product* product_list = NULL;
int num_product = 0;

struct client* client_list = NULL;
int num_client = 0;

struct order* order_list = NULL;
int num_order = 0;


void replace_under(char*);
void replace_space(char*);
void load_list(); //리스트 불러오기
void save_list(int); //리스트 저장하기
void product_add(); // 상품 추가
void product_mod(); // 상품 수정
void product_del(); // 상품 삭제
void client_add(); //고객 추가
void client_mod(); //고객 수정
void client_del(); //고객 삭제
void order_add();
/*
void order_mod();
*/
//추가 예정
void order_del();
void product_search_manage(); //상품 검색
void client_search_manage(); //고객 검색
void order_search_manage(); // 주문 검색
void list_print(int); //통합 완료
void product_manage(); //상품 정보 메뉴
void client_mange(); // 고객 정보 메뉴
void order_manage(); // 주문 정보 메뉴
void manage(); //통합 메뉴
void search_manage(); //검색 메뉴

int main() {
    // 파일에서 상품 목록을 읽어옴
    load_list();

    // 상품 관리 메뉴 실행
    manage();

    // 프로그램 종료 전 상품 목록을 파일에 저장
    for (int i = 1; i <= 3; i++) save_list(i);
    //수정 예정

    // 동적 메모리 해제
    free(product_list);
    free(client_list);
    free(order_list);

    return 0;
}


//공백을 _로 바꾸는 함수
void replace_under(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ') {
            str[i] = '_';
        }
    }
}

//_를 공백으로 바꾸는 함수
void replace_space(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '_') {
            str[i] = ' ';
        }
    }
}

// 파일에서 상품 목록을 읽어옴
void load_list() {

    FILE* p_file;
    FILE* c_file;
    FILE* o_file;

    //product 파일 불러오기
    p_file = fopen("products.txt", "r");
    if (p_file == NULL) {
        printf("상품 파일을 열 수 없습니다.\n\n");
        return;
    }

    // 상품 수를 파일에서 읽어 옴
    fscanf(p_file, "%d", &num_product);

    product_list = (struct product*)malloc(sizeof(struct product) * num_product);

    // 상품 정보를 파일에서 읽어 옴
    for (int i = 0; i < num_product; i++) {
        fscanf(p_file, "%s %d", product_list[i].name, &(product_list[i].price));
    }
    fclose(p_file);


    //client 파일 불러오기
    c_file = fopen("client.txt", "r");
    if (c_file == NULL) {
        printf("고객 파일을 열 수 없습니다.\n");
        return;
    }

    // 고객 수를 파일에서 읽어 옴
    fscanf(c_file, "%d", &num_client);

    client_list = (struct client*)malloc(sizeof(struct client) * num_client);

    // 고객 정보를 파일에서 읽어 옴
    for (int i = 0; i < num_client; i++) {
        replace_under(client_list[i].adress); //주소 밀림 방지
        fscanf(c_file, "%s %s %s", client_list[i].name, client_list[i].adress, client_list[i].phone);
    }
    fclose(c_file);


    //order 파일 불러오기
    o_file = fopen("order.txt", "r");
    if (o_file == NULL) {
        printf("상품 파일을 열 수 없습니다.\n\n");
        return;
    }

    // 주문 수를 파일에서 읽어 옴
    fscanf(o_file, "%d", &num_order);

    order_list = (struct order*)malloc(sizeof(struct order) * num_order);

    // 주문 정보를 파일에서 읽어 옴
    for (int i = 0; i < num_order; i++) {
        fscanf(o_file, "%d %s %s %s %d", &(order_list[i].id), order_list[i].p_name, order_list[i].cli_name, order_list[i].date, &(order_list[i].quantity));
    }
    fclose(o_file);

}

// 상품 목록을 파일에 저장
void save_list(int num) {
    // 상품 목록을 저장할 파일 이름

    FILE* p_file = NULL;
    FILE* c_file = NULL;
    FILE* o_file = NULL;


    switch (num) {

    case 1:
        p_file = fopen("products.txt", "w");
        if (p_file == NULL) {
            printf("상품 파일을 열 수 없습니다.\n");
            fclose(p_file);
            fclose(c_file);
            fclose(o_file);
            return;
        }

        // 상품 수를 파일에 씀
        fprintf(p_file, "%d\n", num_product);

        // 상품 정보를 파일에 씀
        for (int i = 0; i < num_product; i++) {
            fprintf(p_file, "%s %d\n", product_list[i].name, product_list[i].price);
        }
        return;

    case 2:
        c_file = fopen("client.txt", "w");
        if (c_file == NULL) {
            printf("고객 파일을 열 수 없습니다.\n");
            fclose(p_file);
            fclose(c_file);
            fclose(o_file);
            return;
        }

        // 고객 정보를 파일에 씀
        fprintf(c_file, "%d\n", num_client);

        // 고객 정보를 파일에 씀
        for (int i = 0; i < num_client; i++) {
            fprintf(c_file, "%s %s %s\n", client_list[i].name, client_list[i].adress, client_list[i].phone);
            replace_space(client_list[i].adress);
        }

        return;

    case 3:
        o_file = fopen("order.txt", "w");
        if (o_file == NULL) {
            printf(" 파일을 열 수 없습니다.\n");
            fclose(p_file);
            fclose(c_file);
            fclose(o_file);
            return;
        }

        // 주문 정보를 파일에 씀
        fprintf(o_file, "%d\n", num_order);

        // 고객 정보를 파일에 씀
        for (int i = 0; i < num_order; i++) {
            fprintf(o_file, "%d %s %s %s %d\n", order_list[i].id, order_list[i].p_name, order_list[i].cli_name, order_list[i].date, order_list[i].quantity);
        }
        return;

    default:
        printf("수를 잘못입력하셨습니다.\n");
        return;

    }
    fclose(p_file);
    fclose(c_file);
    fclose(o_file);
}

// 상품 추가
void product_add() {
    struct product new_product;

    printf("상품 추가\n\n");
    printf("상품명을 입력해주세요: ");
    scanf("%s", new_product.name);

    printf("가격을 입력해주세요: ");
    scanf("%d", &(new_product.price));

    // 상품 목록에 추가
    num_product++;
    product_list = (struct product*)realloc(product_list, sizeof(struct product) * num_product);
    product_list[num_product - 1] = new_product;

    printf("상품이 추가되었습니다.\n\n");

    // 변경된 상품 목록을 파일에 저장
    save_list(1);
}

//상품 수정
void product_mod() {
    char product_name[20];
    int select, a = 0, found = 0;

    printf("상품 수정 \n");
    printf("수정할 상품명을 입력해주세요: ");
    scanf("%s", product_name);

    for (int i = 0; i < num_product; i++) {
        if (strcmp(product_list[i].name, product_name) == 0) {
            found = 1;

            while (a == 0) {

                printf("1. 상품명\n");
                printf("2. 상품재고\n");
                printf("3. 전부 수정\n");
                printf("수정할 부분을 선택해주세요: \n");
                scanf("%d", &select);

                switch (select) {

                case 1:
                    printf("상품명을 수정해주세요: ");
                    scanf("%s", product_list[i].name);
                    a = 1;
                    break;

                case 2:
                    printf("상품 재고를 수정해주세요: ");
                    scanf("%d", &(product_list[i].price));
                    a = 1;
                    break;

                case 3:
                    printf("상품명을 수정해주세요: ");
                    scanf("%s", product_list[i].name);
                    printf("상품 재고를 수정해주세요: ");
                    scanf("%d", &(product_list[i].price));
                    a = 1;
                    break;

                default:
                    printf("메뉴에 없는 번호 입니다. 다시 입력해주세요.\n");
                }
                if (a == 1) break;
            }
            break;
        }
    }
    if (!found) {
        printf("상품을 찾을 수 없습니다.\n\n");
    }
    save_list(1);
}

// 상품 삭제
void product_del() {

    int num = 1;

    if (num_product == 0) {
        printf("삭제할 상품이 없습니다.\n\n");
        return;
    }

    printf("상품 삭제\n");
    printf("삭제할 상품명을 입력해주세요: ");
    char product_name[20];
    scanf("%s", product_name);

    int found = 0;
    for (int i = 0; i < num_product; i++) {
        if (strcmp(product_list[i].name, product_name) == 0) {
            found = 1;

            // 삭제할 상품 이후의 상품들을 한 칸씩 앞으로 이동

            for (int j = i; j < num_product - 1; j++) {
                product_list[j] = product_list[j + 1];
            }
            num_product--;
            product_list = (struct product*)realloc(product_list, sizeof(struct product) * num_product);
            if (product_list == NULL) {
                printf("product_list에 메모리 재할당을 실패 하였습니다.");
                exit(1);
            }
            printf("상품이 삭제되었습니다.\n\n");
            break;
        }
    }

    if (!found) {
        printf("상품을 찾을 수 없습니다.\n\n");
    }

    // 변경된 상품 목록을 파일에 저장
    save_list(num);
}

//고객 정보 추가
void client_add() {
    struct client new_client;

    printf("고객 정보 추가\n");
    printf("고객님의 성함을 입력해주세요: ");
    scanf("%s", new_client.name);
    while (getchar() != '\n'); //\n 제거


    printf("고객님의 주소를 입력해주세요: ");
    fgets(new_client.adress, sizeof(new_client.adress), stdin);
    new_client.adress[strcspn(new_client.adress, "\n")] = '\0'; //fgets함수를 사용해서 같이 받아진 \n을 제거
    replace_under(new_client.adress);


    printf("고객님의 전화번호를 입력해주세요: ");
    scanf("%s", new_client.phone);
    while (getchar() != '\n');

    //고객 정보 추가
    num_client++;
    client_list = (struct client*)realloc(client_list, sizeof(struct client) * num_client);
    client_list[num_client - 1] = new_client;

    printf("고객님의 정보가 추가되었습니다.\n");

    //고객 정보 목록을 파일에 저장
    save_list(2);
}

//고객 정보 수정
void client_mod() {
    char client_name[20];
    int c_select, b = 0, c_found = 0;

    printf("상품 수정 \n");
    printf("수정할 상품명을 입력해주세요: ");
    scanf("%s", client_name);

    for (int i = 0; i < num_client; i++) {
        if (strcmp(client_list[i].name, client_name) == 0) {
            c_found = 1;

            while (b == 0) {

                printf("1. 고객명\n");
                printf("2. 주소\n");
                printf("3. 전화번호\n");
                printf("4. 전부 수정\n");
                printf("수정할 부분을 선택해주세요: \n");
                scanf("%d", &c_select);
                while (getchar() != '\n');

                switch (c_select) {

                case 1:
                    printf("고객님의 성함을 수정해주세요: ");
                    scanf("%s", client_list[i].name);
                    while (getchar() != '\n');
                    b = 1;
                    break;

                case 2:
                    printf("고객님의 주소를 수정해주세요: ");
                    fgets(client_list[i].adress, sizeof(client_list[i].adress), stdin);
                    client_list[i].adress[strcspn(client_list[i].adress, "\n")] = '\0'; //fgets함수를 사용해서 같이 받아진 \n을 제거
                    replace_under(client_list[i].adress);
                    b = 1;
                    break;

                case 3:
                    printf("고객님의 전화번호를 수정해주세요: ");
                    scanf("%s", client_list[i].phone);
                    while (getchar() != '\n');
                    b = 1;
                    break;
                case 4:
                    printf("고객님의 성함을 수정해주세요: ");
                    scanf("%s", client_list[i].name);
                    while (getchar() != '\n');

                    printf("고객님의 주소를 수정해주세요: ");
                    fgets(client_list[i].adress, sizeof(client_list[i].adress), stdin);
                    client_list[i].adress[strcspn(client_list[i].adress, "\n")] = '\0'; //fgets함수를 사용해서 같이 받아진 \n을 제거
                    replace_under(client_list[i].adress);

                    printf("고객님의 전화번호를 수정해주세요: ");
                    scanf("%s", client_list[i].phone);
                    while (getchar() != '\n');
                    b = 1;
                    break;

                default:
                    printf("메뉴에 없는 번호 입니다. 다시 입력해주세요.\n");
                }
                if (b == 1) break;
            }
            break;
        }
    }
    if (!c_found) {
        printf("고객님의 정보를 찾을 수 없습니다.\n\n");
    }
    save_list(2);
}

// 고객 정보 삭제
void client_del() {

    int num = 1;

    if (num_client == 0) {
        printf("삭제할 고객이 없습니다.\n\n");
        return;
    }

    printf("고객 삭제\n");
    printf("삭제할 고객명을 입력해주세요: ");
    char client_name[20];
    scanf("%s", client_name);

    int found = 0;
    for (int i = 0; i < num_client; i++) {
        if (strcmp(client_list[i].name, client_name) == 0) {
            found = 1;

            // 삭제할 고객 이후의 고객들을 한 칸씩 앞으로 이동

            for (int j = i; j < num_client - 1; j++) {
                client_list[j] = client_list[j + 1];
            }
            num_client--;
            client_list = (struct client*)realloc(client_list, sizeof(struct client) * num_client);
            if (client_list == NULL) {
                printf("client_list에 메모리 재할당을 실패 하였습니다.");
                exit(1);
            }
            printf("고객이 삭제되었습니다.\n\n");
            break;
        }
    }

    if (!found) {
        printf("고객을 찾을 수 없습니다.\n\n");
    }
}

// 주문 정보 추가
void order_add() {
    struct order new_order;
    int num = 1;

    printf("주문 추가\n\n");

    printf("상품명을 입력해주세요: ");
    scanf("%s", new_order.p_name);

    printf("주문자를 입력해주세요: ");
    scanf("%s", new_order.cli_name);

    printf("수량을 입력해주세요: ");
    scanf("%d", &(new_order.quantity));

    printf("주문 날짜는 현재 날짜로 추가됩니다.\n ");
    //주문 날짜
    time_t currentTime;
    time(&currentTime);
    struct tm* timeInfo = localtime(&currentTime);
    char timeString[50];
    strftime(timeString, sizeof(timeString), "%Y/%m/%d", timeInfo);
    strcpy(new_order.date, timeString);

    // 상품 목록에 추가
    num_order++;
    order_list = (struct order*)realloc(order_list, sizeof(struct order) * num_order);
    order_list[num_order - 1] = new_order;

    printf("주문이 완료되었습니다.\n\n");

    // 변경된 상품 목록을 파일에 저장
    save_list(num);
}
// 주문 삭제
void order_del() {

    int num = 1;

    if (num_order == 0) {
        printf("삭제할 주문이 없습니다.\n\n");
        return;
    }

    printf("주문 삭제\n");
    printf("삭제할 주문명을 입력해주세요: ");
    char order_name[20];
    scanf("%s", order_name);

    int found = 0;
    for (int i = 0; i < num_order; i++) {
        if (strcmp(order_list[i].p_name, order_name) == 0) {
            found = 1;

            // 삭제할 주문 이후의 주문들을 한 칸씩 앞으로 이동

            for (int j = i; j < num_order - 1; j++) {
                order_list[j] = order_list[j + 1];
            }
            num_order--;
            order_list = (struct order*)realloc(order_list, sizeof(struct order) * num_order);
            if (order_list == NULL) {
                printf("order_list에 메모리 재할당을 실패 하였습니다.");
                exit(1);
            }
            printf("주문이 삭제되었습니다.\n\n");
            break;
        }
    }

    if (!found) {
        printf("주문을 찾을 수 없습니다.\n\n");
    }
}

//상품 검색
void product_search_manage() {

    char search_t[20];
    int choice, s_price, found;

    while (1) {
        printf("검색할 항목을 선택해주세요\n\n");
        printf("0. 메뉴로 돌아가기\n");
        printf("1. 상품명\n");
        printf("2. 상품 가격\n");
        printf("입력: ");
        scanf("%d", &choice);

        switch (choice) {

        case 0:
            return;

        case 1:
            printf("\n검색할 상품명을 입력해주세요: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_product; i++) {
                if (strcmp(product_list[i].name, search_t) == 0) {
                    found = 1;
                    printf("상품명: %s\n", product_list[i].name);
                    printf("가격: %d\n", product_list[i].price);
                    printf("----------------------------\n");
                }
            }
            if (!found) printf("검색 결과가 없습니다.\n\n");

            found = 0;

            break;

        case 2:
            printf("\n검색할 가격을 입력해주세요: ");
            scanf("%d", &s_price);
            for (int i = 0; i < num_product; i++) {
                if (product_list[i].price == s_price) {
                    found = 1;
                    printf("상품명: %s\n", product_list[i].name);
                    printf("가격: %d\n", product_list[i].price);
                    printf("----------------------------\n");
                }
            }
            if (!found) printf("\n검색 결과가 없습니다.\n\n");

            found = 0;

            break;

        default:
            printf("\n잘못된 입력입니다. 다시 입력해주세요.\n\n");
            break;
        }

    }

}

//고객 검색
void client_search_manage() {

    char search_t[20];
    int choice, found;

    while (1) {
        printf("\n검색할 항목을 선택해주세요\n\n");
        printf("0. 메뉴로 돌아가기\n");
        printf("1. 고객명\n");
        printf("2. 고객 주소\n");
        printf("3. 전화 번호\n");
        printf("입력: ");
        scanf("%d", &choice);

        switch (choice) {

        case 0:
            return;

        case 1:
            printf("\n검색할 고객명을 입력해주세요: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_client; i++) {
                if (strcmp(client_list[i].name, search_t) == 0) {
                    found = 1;
                    printf("고객명: %s\n", client_list[i].name);
                    printf("고객 주소: %s\n", client_list[i].adress);
                    printf("휴대전화: %s\n", client_list[i].phone);
                    printf("----------------------------\n");
                }
            }
            if (!found) printf("\n검색 결과가 없습니다.\n\n");

            found = 0;

            break;

        case 2:
            printf("\n검색할 주소를 입력해주세요: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_client; i++) {
                if (strcmp(client_list[i].adress, search_t) == 0) {
                    found = 1;
                    printf("고객명: %s\n", client_list[i].name);
                    printf("고객 주소: %s\n", client_list[i].adress);
                    printf("휴대전화: %s\n", client_list[i].phone);
                    printf("----------------------------\n");
                }
            }
            if (!found) printf("\n검색 결과가 없습니다.\n\n");

            found = 0;

            break;

        case 3:
            printf("\n검색할 전화번호를 입력해주세요: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_client; i++) {
                if (strcmp(client_list[i].phone, search_t) == 0) {
                    found = 1;
                    printf("고객명: %s\n", client_list[i].name);
                    printf("고객 주소: %s\n", client_list[i].adress);
                    printf("휴대전화: %s\n", client_list[i].phone);
                    printf("----------------------------\n");
                }
            }
            if (!found) printf("\n검색 결과가 없습니다.\n\n");

            found = 0;

            break;

        default:
            printf("\n잘못된 입력입니다. 다시입력해주세요.\n\n");
            break;
        }
    }

}

//주문 검색
void order_search_manage() {

    char search_t[20];
    int choice, found, isearch_t;

    while (1) {
        printf("\n검색할 항목을 선택해주세요\n\n");
        printf("0. 메뉴로 돌아가기\n");
        printf("1. 상품명\n");
        printf("2. 주문자\n");
        printf("3. 주문 날짜\n");
        printf("4. 주문 id\n");
        printf("입력: ");
        scanf("%d", &choice);

        switch (choice) {

        case 0:
            return;

        case 1:
            printf("\n검색할 상품명을 입력해주세요: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_order; i++) {
                if (strcmp(order_list[i].p_name, search_t) == 0) {
                    found = 1;
                    printf("주문 id: %d\n", order_list[i].id);
                    printf("상품명: %s\n", order_list[i].p_name);
                    printf("주문 수량: %d\n", order_list[i].quantity);
                    printf("주문자: %s\n", order_list[i].cli_name);
                    printf("주문 날짜: %s\n", order_list[i].date);
                    printf("----------------------------\n");
                }
            }
            if (!found) printf("\n검색 결과가 없습니다.\n\n");

            found = 0;

            break;

        case 2:
            printf("\n검색할 주문자명을 입력해주세요: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_order; i++) {
                if (strcmp(order_list[i].cli_name, search_t) == 0) {
                    found = 1;
                    printf("주문 id: %d\n", order_list[i].id);
                    printf("상품명: %s\n", order_list[i].p_name);
                    printf("주문 수량: %d\n", order_list[i].quantity);
                    printf("주문자: %s\n", order_list[i].cli_name);
                    printf("주문 날짜: %s\n", order_list[i].date);
                    printf("----------------------------\n");
                }
            }
            if (!found) printf("\n검색 결과가 없습니다.\n\n");

            found = 0;

            break;

        case 3:
            printf("검색할 주문 날짜를 입력해주세요: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_order; i++) {
                if (strcmp(order_list[i].date, search_t) == 0) {
                    found = 1;
                    printf("주문 id: %d\n", order_list[i].id);
                    printf("상품명: %s\n", order_list[i].p_name);
                    printf("주문 수량: %d\n", order_list[i].quantity);
                    printf("주문자: %s\n", order_list[i].cli_name);
                    printf("주문 날짜: %s\n", order_list[i].date);
                    printf("----------------------------\n");
                }
            }
            if (!found) printf("\n검색 결과가 없습니다.\n\n");

            found = 0;

            break;

        case 4:
            printf("검색할 주문 id를 입력해주세요: ");
            scanf("%d", &isearch_t);
            for (int i = 0; i < num_order; i++) {
                if (order_list[i].id == isearch_t) {
                    found = 1;
                    printf("주문 id: %d\n", order_list[i].id);
                    printf("상품명: %s\n", order_list[i].p_name);
                    printf("주문 수량: %d\n", order_list[i].quantity);
                    printf("주문자: %s\n", order_list[i].cli_name);
                    printf("주문 날짜: %s\n", order_list[i].date);
                    printf("----------------------------\n");
                }
            }
            if (!found) printf("\n검색 결과가 없습니다.\n\n");

            found = 0;

            break;


        default:
            printf("\n잘못된 입력입니다. 다시 입력해주세요.\n\n");
            break;
        }

    }


}

//목록 출력
void list_print(int num) {

    switch (num) {

    case 1:
        printf("상품 목록\n\n");
        printf("----------------------------\n\n");
        for (int i = 0; i < num_product; i++) {
            printf("상품명: %s\n", product_list[i].name);
            printf("가격: %d\n\n", product_list[i].price);
            printf("----------------------------\n\n");
        }
        break;

    case 2:
        printf("고객 목록\n\n");
        printf("----------------------------\n\n");
        for (int i = 0; i < num_client; i++) {
            printf("상품명: %s\n", client_list[i].name);
            printf("주소: %s\n", client_list[i].adress);
            printf("휴대전화: %s\n\n", client_list[i].phone);
            printf("----------------------------\n\n");
        }
        break;

    case 3:
        printf("주문 목록\n\n");
        printf("----------------------------\n\n");
        for (int i = 0; i < num_order; i++) {
            printf("상품명: %d\n", order_list[i].id);
            printf("가격: %s\n", order_list[i].p_name);
            printf("가격: %s\n", order_list[i].cli_name);
            printf("가격: %s\n", order_list[i].date);
            printf("가격: %d\n\n", order_list[i].quantity);
            printf("----------------------------\n\n");
        }
        break;
    }

}// 통합

//관리 메뉴
void product_manage() {
    int choice;

    while (1) {
        printf("1. 상품 추가 메뉴\n");
        printf("2. 상품 수정 메뉴\n");
        printf("3. 상품 삭제 메뉴\n");
        printf("4. 상품 목록 출력\n");
        printf("5. 메뉴로 돌아가기\n");
        printf("0. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            exit(1);
        case 1:
            product_add();
            break;

        case 2:
            product_mod();
            break;

        case 3:
            product_del();
            break;

        case 4:
            list_print(1);
            break;

        case 5:
            return;

        default:
            printf("잘못된 입력입니다. 다시 입력해주세요.\n");
            break;
        }
    }
}

void client_manage() {
    int choice;

    while (1) {
        printf("1. 고객 추가 메뉴\n");
        printf("2. 고객 수정 메뉴\n");
        printf("3. 고객 삭제 메뉴\n");
        printf("4. 고객 목록 출력\n");
        printf("5. 메뉴로 돌아가기\n");
        printf("0. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            exit(1);
        case 1:
            client_add();
            break;

        case 2:
            client_mod();
            break;

        case 3:
            client_del();
            break;

        case 4:
            list_print(2);
            break;

        case 5:
            return;

        default:
            printf("잘못된 입력입니다. 다시 입력해주세요.\n");
            break;
        }
    }
}

void order_manage() {
    int choice;

    while (1) {
        printf("1. 주문 추가 메뉴\n");
        printf("2. 주문 수정 메뉴\n");
        printf("3. 주문 삭제 메뉴\n");
        printf("4. 주문 목록 출력\n");
        printf("5. 메뉴로 돌아가기\n");
        printf("0. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            exit(1);
        case 1:
            // order_add();
            break;

        case 2:
            // order_mod();
            break;

        case 3:
            order_del();
            break;

        case 4:
            list_print(3);
            break;

        case 5:
            return;

        default:
            printf("잘못된 입력입니다. 다시 입력해주세요.\n");
            break;
        }
    }
}

void manage() {
    int choice;

    while (1) {
        printf("1. 상품 메뉴\n");
        printf("2. 고객 메뉴\n");
        printf("3. 주문 메뉴\n");
        printf("4. 검색 메뉴\n");
        printf("0. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            exit(1);
        case 1:
            product_manage();
            break;

        case 2:
            client_manage();
            break;

        case 3:
            order_manage();
            break;

        case 4:
            search_manage();

        default:
            printf("잘못된 입력입니다. 다시 입력해주세요.\n");
            break;
        }
    }
}

void search_manage() {

    int choice;

    while (1) {
        printf("검색 할 정보를 선택해주세요\n");
        printf("0. 메뉴로 돌아가기\n");
        printf("1. 상품 정보\n");
        printf("2. 고객 정보\n");
        printf("3. 주문 정보\n");
        printf("입력: ");
        scanf("%d", &choice);

        switch (choice) {

        case 0:
            return;

        case 1:
            product_search_manage();
            break;

        case 2:
            client_search_manage();
            break;

        case 3:
            order_search_manage();
            break;

        default:
            printf("잘못된 입력입니다. 다시 입력해주세요.");
            break;
        }
    }
}
