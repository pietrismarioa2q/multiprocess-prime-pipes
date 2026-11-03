#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

struct Range {
    int start;
    int end;
};

bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    const int NUM_PROCESSES = 10;
    const int RANGE_SIZE = 1000;

    int parent_to_child[NUM_PROCESSES][2];
    int child_to_parent[NUM_PROCESSES][2];
    pid_t pids[NUM_PROCESSES];

    for (int i = 0; i < NUM_PROCESSES; ++i) {
        if (pipe(parent_to_child[i]) == -1 || pipe(child_to_parent[i]) == -1) {
            std::cerr << "Eroare la crearea pipe-ului" << std::endl;
            return 1;
        }

        pids[i] = fork();
        if (pids[i] < 0) {
            std::cerr << "Eroare la fork" << std::endl;
            return 1;
        }

        if (pids[i] == 0) {
            close(parent_to_child[i][1]);
            close(child_to_parent[i][0]);

            Range range;
            read(parent_to_child[i][0], &range, sizeof(Range));
            close(parent_to_child[i][0]);

            for (int num = range.start; num <= range.end; ++num) {
                if (isPrime(num)) {
                    write(child_to_parent[i][1], &num, sizeof(int));
                }
            }

            int EOF_SIGNAL = -1;
            write(child_to_parent[i][1], &EOF_SIGNAL, sizeof(int));
            close(child_to_parent[i][1]);
            return 0;
        } else {
            close(parent_to_child[i][0]);
            close(child_to_parent[i][1]);
        }
    }

    for (int i = 0; i < NUM_PROCESSES; ++i) {
        Range r = { i * RANGE_SIZE + 1, (i + 1) * RANGE_SIZE };
        write(parent_to_child[i][1], &r, sizeof(Range));
        close(parent_to_child[i][1]);
    }

    int total_primes = 0;
    std::cout << "====================================================\n";
    std::cout << "  REZULTATE CAUTARE NUMERE PRIME (LINUX - POSIX)    \n";
    std::cout << "====================================================\n\n";

    for (int i = 0; i < NUM_PROCESSES; ++i) {
        int start_r = i * RANGE_SIZE + 1;
        int end_r = (i + 1) * RANGE_SIZE;
        std::cout << ">>> Proces Copil [" << pids[i] << "] | Interval [" << start_r << " - " << end_r << "]:\n";

        int prime_val;
        int count = 0;
        while (read(child_to_parent[i][0], &prime_val, sizeof(int)) > 0) {
            if (prime_val == -1) break;
            std::cout << prime_val << " ";
            count++;
        }
        total_primes += count;
        std::cout << "\n[Total gasite in interval: " << count << "]\n\n";
        close(child_to_parent[i][0]);
    }

    for (int i = 0; i < NUM_PROCESSES; ++i) {
        waitpid(pids[i], NULL, 0);
    }

    std::cout << "====================================================\n";
    std::cout << "Total numere prime gasite de la 1 la 10000: " << total_primes << "\n";
    std::cout << "====================================================\n";

    return 0;
}

