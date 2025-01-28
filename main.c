#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void generateFibonacci(int n) {
    long long int first = 0, second = 1, next;

    if (n == 1) {
        printf("Fibonacci result for %d term: %lld\n", n, first);
        return;
    }

    for (int i = 2; i <= n; i++) {
        next = first + second;
        first = second;
        second = next;
    }

    printf("Fibonacci result for %d term: %lld\n", n, second);
}

int main() {
    int n;
    printf("Enter a number for Fibonacci calculation: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a positive integer greater than 0.\n");
        exit(1);
    }

    pid_t pid1, pid2;

    // İlk fork: P1 oluşturulur
    pid1 = fork();

    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid1 == 0) {
        // P1 süreci
        printf("Process P1 with PID %d created by P0 (PID %d)\n", getpid(), getppid());
        exit(0);
    } else {
        // Ana süreç (P0)
        wait(NULL); // P1'in tamamlanmasını bekler

        // İkinci fork: P2 oluşturulur
        pid2 = fork();

        if (pid2 < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid2 == 0) {
            // P2 süreci
            printf("Process P2 with PID %d created by P0 (PID %d)\n", getpid(), getppid());
            generateFibonacci(n);
            exit(0);
        } else {
            // P0 süreci
            wait(NULL); // P2'nin tamamlanmasını bekler
        }
    }

    printf("Parent process (P0) with PID %d terminated.\n", getpid());
    return 0;
}
