#include <iostream>
#include <vector>


int FindLowerAce(std::vector<std::vector<int>>& sets){
    int min_id = 0;
    int len_to_ace = 100;

    for (int i = 0; i < sets.size(); ++i){
        // проверяем каждую кучу
        for (int j = sets[i].size() - 1; j >= 0; --j){
            // идем с верха кучи вниз и ищем туз (с конца ветора в начало)
            if (sets[i][j] == 14){
                // если это туз
                if (sets[i].size() - 1 - j < len_to_ace){
                    // если он наименьший из проверенных
                    len_to_ace = sets[i].size() - 1 - j;
                    min_id = i;
                } else {
                    // иначе проверяем следующую кучу
                    break;
                }
            } else if (j > 0 && sets[i][j - 1] - sets[i][j] != 1) {
                // если же это не туз, то проверяем, что есть порядок до этого туза
                break;
            }
        }
    }

    int exit_code = -1;
    if (len_to_ace != 100) {
        // если все таки нашелся подходящий туз
        exit_code = min_id;
    }

    return exit_code;
}

int FindNextElementId(std::vector<std::vector<int>>& sets, int next_element, int except_id) {
    int exit_code = -1;

    for (int i = 0; i < sets.size(); ++i) {
        if (i != except_id) {
            // найдем в какой куче находится следующий элемент для собираемого набора
            if (sets[i][sets[i].size() - 1] == next_element) {
                // допустим, мы нашли такую кучу
                exit_code = i;
                break;
            }
        }
    }

    return exit_code;
}

bool TryDeleteSet(std::vector<std::vector<int>>& sets, int lower_ace_id) {
    bool exit_code = false;

    if (sets[lower_ace_id][sets[lower_ace_id].size() - 1] == 6) {
                  // если есть собранный набор, то удалим его
        sets[lower_ace_id].resize(sets[lower_ace_id].size() - 9);
        exit_code = true;
    }

    return exit_code;
}

void Print(std::vector<std::vector<int>>& sets) {
    for (int i = 0; i < sets.size(); ++i) {
        for (int j = 0; j < sets[i].size(); ++j) {
            std::cout << sets[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "-------------------\n\n";
}

int main() {
    std::vector<std::vector<int>> sets (8, std::vector<int> (9));
    freopen("test_yes.tst", "r", stdin);
    // считывание
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cin >> sets[i][j];
            sets[i][j] += 5;
        }
    }

    int exit_code = 1;
    int cnt = 8;

    while (cnt > 0) {
        int lower_ace_id = FindLowerAce(sets);
        if (lower_ace_id == -1){
            // проверим, нашелся ли доступный туз (еще и самый верхний)
            exit_code = -1;
            break;
        }

        // для начала проверим, не собранный ли набор там где туз
        bool is_set_completed = TryDeleteSet(sets, lower_ace_id);

        // проверим, не лежит ли туз сверху и есть ли пустая куча (если все таки не удалили набор)
        if (sets[lower_ace_id][sets[lower_ace_id].size() - 1] == 14 && !is_set_completed) {
            // да, лежит
            for (int i = 0; i < sets.size(); ++i) {
                if (sets[i].empty()) {
                    // да, еще есть пустая куча. тогда перекладываем этот туз в эту кучу
                    sets[i].push_back(14);
                    sets[lower_ace_id].pop_back();
                    // изменяем id набора, который будем собирать (там, где теперь лежит туз)
                    lower_ace_id = i;
                    break;
                }
            }
        }

        // окей, мы нашли подходящий туз. пора собирать набор (опять таки, если он не был собран)
        while (!is_set_completed) {
            Print(sets);
            // ищем следующий элемент набора в остальных кучах
            int next_element = sets[lower_ace_id][sets[lower_ace_id].size() - 1] - 1;
            int next_element_id = FindNextElementId(sets, next_element, lower_ace_id);
            if (next_element_id == -1) {
                // проверим, нашелся ли подходящий элемент для собирания набора
                exit_code = -1;
                break;
            }
            // окей, нашелся такой элемент, тогда переложим его в нужное место
            sets[lower_ace_id].push_back(sets[next_element_id][sets[next_element_id].size() - 1]);
            // проверим, не является ли этот элемент 6 (тогда нужно удалить собранный набор)
            is_set_completed = TryDeleteSet(sets, lower_ace_id);
            // и удалить сам элемент из изначальной кучи, где его нашли
            sets[next_element_id].pop_back();
        }
        // если мы еще здесь, значит мы успешно собрали 1 набор. повторяе дальше)
        --cnt;
    }

    if (exit_code == 1) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    fclose(stdin);
    return 0;
}