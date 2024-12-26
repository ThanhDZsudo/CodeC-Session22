#include <stdio.h>
#define MAX 100

typedef struct {
    int id;
    char name[100];
    int age;
} SinhVien;

void ghiTep(SinhVien sinhVienList[], int count) {
    FILE *file = fopen("sinhvien.dat", "wb");
    if (file == NULL) {
        printf("Khong the mo tep!\n");
        return;
    }
    fwrite(sinhVienList, sizeof(SinhVien), count, file);
    fclose(file);
}

int docTep(SinhVien sinhVienList[]) {
    FILE *file = fopen("sinhvien.dat", "rb");
    if (file == NULL) {
        printf("Khong the mo tep!\n");
        return 0;
    }
    int count = 0;
    while (fread(&sinhVienList[count], sizeof(SinhVien), 1, file)) {
        count++;
    }
    fclose(file);
    return count;
}

void themSinhVien(SinhVien sinhVienList[], int *count) {
    if (*count >= MAX) {
        printf("Danh sach sinh vien da day!\n");
        return;
    }
    SinhVien sv;
    printf("Nhap ID: ");
    scanf("%d", &sv.id);
    getchar();
    printf("Nhap Ten: ");
    fgets(sv.name, sizeof(sv.name), stdin);
    sv.name[strcspn(sv.name, "\n")] = 0;
    printf("Nhap Tuoi: ");
    scanf("%d", &sv.age);
    sinhVienList[*count] = sv;
    (*count)++;
    ghiTep(sinhVienList, *count);
}

void suaSinhVien(SinhVien sinhVienList[], int count) {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (sinhVienList[i].id == id) {
            printf("Nhap Ten moi: ");
            getchar();
            fgets(sinhVienList[i].name, sizeof(sinhVienList[i].name), stdin);
            sinhVienList[i].name[strcspn(sinhVienList[i].name, "\n")] = 0;
            printf("Nhap Tuoi moi: ");
            scanf("%d", &sinhVienList[i].age);
            ghiTep(sinhVienList, count);
            return;
        }
    }
    printf("Sinh vien khong ton tai!\n");
}

void xoaSinhVien(SinhVien sinhVienList[], int *count) {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < *count; i++) {
        if (sinhVienList[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                sinhVienList[j] = sinhVienList[j + 1];
            }
            (*count)--;
            ghiTep(sinhVienList, *count);
            return;
        }
    }
    printf("Sinh vien khong ton tai!\n");
}

void timKiemSinhVien(SinhVien sinhVienList[], int count) {
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (sinhVienList[i].id == id) {
            printf("ID: %d, Ten: %s, Tuoi: %d\n", sinhVienList[i].id, sinhVienList[i].name, sinhVienList[i].age);
            return;
        }
    }
    printf("Sinh vien khong ton tai!\n");
}

void sortSinhVien(SinhVien sinhVienList[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(sinhVienList[i].name, sinhVienList[j].name) > 0) {
                SinhVien temp = sinhVienList[i];
                sinhVienList[i] = sinhVienList[j];
                sinhVienList[j] = temp;
            }
        }
    }
    ghiTep(sinhVienList, count);
}

void hienThiMenu() {
    printf("\nTHUC DON\n");
    printf("1. Them sinh vien\n");
    printf("2. Sua thong tin sinh vien\n");
    printf("3. Xoa sinh vien\n");
    printf("4. Tim kiem sinh vien\n");
    printf("5. Sap xep danh sach sinh vien\n");
    printf("6. Thoat\n");
    printf(" ");
}

int main() {
    SinhVien sinhVienList[MAX];
    int count = docTep(sinhVienList);
    int luaChon;
    do {
        hienThiMenu();
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                themSinhVien(sinhVienList, &count);
                break;
            case 2:
                suaSinhVien(sinhVienList, count);
                break;
            case 3:
                xoaSinhVien(sinhVienList, &count);
                break;
            case 4:
                timKiemSinhVien(sinhVienList, count);
                break;
            case 5:
                sortSinhVien(sinhVienList, count);
                break;
            case 6:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (luaChon != 6);

    return 0;
}

