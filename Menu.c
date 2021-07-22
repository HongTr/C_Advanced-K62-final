#include "Graphlib.h"

int main(){
    FILE* source;
    source = fopen("dothi.txt", "r");
    if (source == NULL){
        printf("Error!\n");
        exit(1);
    }
    Graph graph = createGraph();
    int choice, flag = 0;
    do{
        printf("=====================================\n");
        printf("1. Doc ban do; In ma tran ke\n");
        printf("2. In danh sach ke\n");
        printf("3. In danh sach\n");
        printf("4. Tim duong di ngan nhat\n");
        printf("5. Tim duong di bo ngan nhat\n");
        printf("6. Thoat\n");
        printf("=====================================\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        if (choice <= 0 || choice >= 7) printf("Nhap khong hop le!\n");
        else if (choice >=1 && choice <=6 && choice != 3){
            switch(choice){
                case 1:
                    if(flag == 1) printf("Ban da doc ban do!");
                    else{
                        flag = 1;
                        int v, e, v1, v2;
                        float w;
                        fscanf(source, "%d %d", &v, &e);
                        int matran[(v+1)*(v+1)];
                        for (int i = 0; i < (v+1)*(v+1); i++) matran[i] = 0;
                        for (int i = 0; i < e; i++){ //Add Edge
                            fscanf(source, "%d\t%d\t%f", &v1, &v2, &w);
                            addEdge2(graph, v1, v2, w);
                            matran[v1 *(v+1) + v2] = 1;
                            matran[v2* (v+1) + v1] = 1;
                        }
                        printf("MA TRAN KE\n");
                        for (int i = 0; i <= v; i++){
                            for (int j = 0; j <= v; j++) printf("%d ", matran[i*(v+1)+j]);
                            printf("\n");
                        }
                    }
                    break;
                case 2:
                    if (flag == 1){
                        JRB trav;
                        jrb_traverse(trav, graph.edges){
                            int index = jval_i(trav->key);
                            printf("Castle %d: ", index);
                            int n, output[10];
                            n = outdegree(graph, index, output);
                            for (int i = 0; i < n; i++) printf("%d ", output[i]);
                            printf("\n");
                        }
                    }
                    else printf("Ban chua nap do thi!\n");
                    break;
                case 4:
                    if (flag){
                        int s, t;
                        printf("Xuat phat: "); scanf("%d", &s);
                        printf("Ket thuc: "); scanf("%d", &t);
                        int path[100];
                        int l;
                        double weight = dijkstra(graph, s, t, path, &l);
                        printf("FUCK\n");
                        if (weight == INFINITIVE_VALUE) printf("ROUTE NOT FOUND\n");
                        else{
                            printf("Length: %.lf\n", weight);
                            printf("Path: ");
                            for (int i = 0; i < l; i++) printf("%d ", path[i]);
                            printf("\n");
                        }
                        break;
                    }
                    else printf("Ban chua doc ban do!\n");
                case 5:
                    break;
                case 6: printf("Ban da thoat chuong trinh!\n");
                    break;
            }
        }
    }while(choice != 6);
    fclose(source);
    return 1;
}