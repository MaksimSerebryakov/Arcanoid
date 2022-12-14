# Arkanoid
На основе имеющегося проекта необходимо реализовать классическую игру Arkanoid - https://ru.wikipedia.org/wiki/Arkanoid
### Требования по геймплею
 - **Игра должна корректно работать на всём диапазоне входных значений `ArkanoidSettings`.**
 - Блоки прямоугольной формы, количество линий и столбцов и расстояние между ними определяется исходя из входных данных функции `Arkanoid::reset`.
 - Шар - окружность с радиусом заданным параметрами функции `Arkanoid::reset`.
 - Начальная скорость полета шара задается входными параметрами функции `Arkanoid::reset`.
 - Каретка прямоугольной формы с шириной заданной параметрами функции `Arkanoid::reset`. 
 - Каретка должа управляться пользователем клавишами `A` (движение влево) и `D` (движение вправо).
 - Данные в `ArkanoidDebugData` должны корректно добавлятся на каждом вызове `Arkanoid::update`.
 - ***Приветствуется любой креатив - как игрового процесса, так и отладочной отрисовки, читов.***
 
### Требования по реализации
 - Стабильная работа приложения
 - Разумное оформление кода - понятная архитектура, внимание к именам типов и переменных, читаемость кода