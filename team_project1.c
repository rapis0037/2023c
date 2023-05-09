#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void load_list(); //통합 완료
void save_list(int); //통합 완료
void product_add();
void product_del();
void product_mod();
/*
void client_add();
void client_mod();
void client_del();
void order_add();
void order_mod();
void order_del();

*/
//추가 예정
void list_print(int); //통합 완료
void product_manage();
void client_mange();
void order_manage();
void manage();

int main() {
    // 파일에서 상품 목록을 읽어옴
    load_list();

    // 상품 관리 메뉴 실행
    manage();

    // 프로그램 종료 전 상품 목록을 파일에 저장
    for(int i = 1; i <= 3; i++) save_list(i);
    //수정 예정

    // 동적 메모리 해제
    free(product_list);
    free(client_list);
    free(order_list);

    return 0;
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

        // 고객 정보를 파일에 씀
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
            if(product_list == NULL){
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
        printf("0. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            exit(1);
        case 1:
            //client_add();
            break;

        case 2:
            //client_mod();
            break;

        case 3:
            //client_del();
            break;

        case 4:
            list_print(2); //통합 예정
            break;
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
            //order_del();
            break;

        case 4:
            list_print(3);
            break;
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
            //client_manage();
            break;

        case 3:
            //order_manage(); 
            break;

        default:
            printf("잘못된 입력입니다. 다시 입력해주세요.\n");
            break;
        }
    }
}
