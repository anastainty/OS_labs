#include "BankAcc.cpp"
#include "Operations.cpp"

int main(int argc, char **argv)
{
    std::vector<float> scene_0({-3, 5, -1, 5});
    std::vector<float> scene_1({10, -16, 20});
    std::vector<float> scene_2;
    scene_2.reserve(argc - 1);
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            scene_2.push_back(std::stof(argv[i]));
        }
    }

    BankAcc bankAcc;
    std::thread thread_0(&Operations::startOperations, Operations(scene_0, &bankAcc));
    std::thread thread_1(&Operations::startOperations, Operations(scene_1, &bankAcc));
    std::thread thread_2(&Operations::startOperations, Operations(scene_2, &bankAcc));

    thread_0.join();
    thread_1.join();
    thread_2.join();
    return 0;
}
