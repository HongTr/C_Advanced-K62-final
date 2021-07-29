#include "Graphlib.h"
int v, e;
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
                        int v1, v2, w;
                        fscanf(source, "%d %d", &v, &e);
                        int matran[(v+1)*(v+1)];
                        for (int i = 0; i < (v+1)*(v+1); i++) matran[i] = 0;
                        while(!feof(source)){ //Add Edge
                            fscanf(source, "%d\t%d\t%d", &v1, &v2, &w);
                            addEdge2(graph, v1, v2, w);
                            addVertex(graph, v1, "name");
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
                        fflush(stdin);
                        int start, stop;
                        printf("Input start: "); scanf("%d", &start);
                        printf("Input stop: "); scanf("%d", &stop);
                        int length, path[100];
                        int weight = dijkstra(graph, start, stop, path, &length);
                        if (weight == INFINITIVE_VALUE) printf("No path between Castle %d and Castle %d\n", start, stop);
                        else {
                            printf("Path between Castle %d and Castle %d: ", start, stop);
                            for (int i=0; i<length; i++) printf("Castle %d ", path[i]); printf("\n");
                            printf("Total weight: %d", weight);
                        }
                        printf("\n");
                    }
                    else printf("Ban chua nap danh sach!\n");
                    break;
                case 5:
                    break;
                case 6: printf("Ban da thoat chuong trinh!\n");
                    break;
            }
        }
        else{
            if(flag){
                int chon;
                printf("3.1 Danh sach cac thanh tri chi co the di bo den\n");
                printf("3.2 Thanh tri co nhieu duong den nhat\n");
                printf("Ban chon: ");
                scanf("%d", &chon);
                switch(chon){
                    case 1:;
                        int* walk = (int*)calloc(v+1, sizeof(int));
                        JRB node;
                        jrb_traverse(node, graph.edges){
                            JRB check;
                            JRB list_ = (JRB)jval_v(node->val);
                            jrb_traverse(check, list_){
                                if ((int)jval_v(check->val) < 50) walk[jval_i(check->key)] = 1;
                            }
                        }
                        printf("Di bo: ");
                        for (int i = 1; i<v+1; i++){
                            if (walk[i] == 0) printf("%d ", i);
                        }
                        printf("\n");
                        break;
                    case 2:;
                        int max = -1;
                        int* list_of_adj = (int*)malloc((v+1)*sizeof(int));
                        JRB temp;
                        jrb_traverse(temp, graph.edges){
                            int* linhtinh = (int*)malloc((v+1)*sizeof(int));
                            int index = jval_i(temp->key);
                            list_of_adj[index] = getAdjacentVertices(graph, index, linhtinh);
                        }
                        printf("Duong di max: ");
                        for (int i = 1; i < v+1; i++){
                            if (list_of_adj[i] > max) max = list_of_adj[i];
                        }
                        for (int i = 1; i < v+1; i++){
                            if (max == list_of_adj[i]) printf("%d ", i);
                        }
                        printf("\n");
                        break;
                }
            }
            else printf("Ban chua doc ban do!\n");
        }
    }while(choice != 6);
    fclose(source);
    return 1;
}