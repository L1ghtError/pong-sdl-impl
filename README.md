# pong-sdl-impl
## To get the exe file, go to the release and install zip with bin files
### library used: SDL2 and several auxiliary libraries
## Вимоги
1. Показати знання мови C++ (не С).
```
В цьому проєкті були створені класи (Moving_base - базовий клас який реалізує основний функціонал усіх рухомих об'єктів,
Moving_Pedal - клас який реалізує  рух платформ
Moving_Ball - клас який реалізує  рух шару та відтворює звуки зітнень 
), використаний оператор перетворення типу static_cast та розумні вказівники (unique_ptr)
```
2. Показати знання ООП та вміння його використовувати.
```
В цьому проєкті я використав наслідування,інкапсуляцію та поліморфізм
```
3. Показати вміння використовувати STL (контейнери, розумні вказівники).
```
В цьому проєкті був використаний stl контейнер (vector)
```
4. Акуратно оформлений структурований код. Код має бути відформатованим. За бажанням можна використати інструмент clang-format або будь-який інший. Відео інструкція як це зробити с clang-format
```
Код розбитий по ріним методам класів Moving_Pedal, Moving_Ball, Moving_Base та GameBackend.
Для форматування я використав стандартний форматувальник visual studio
```
6. Показати вміння підключати та використовувати зовнішні бібліотеки.
```
В цьому проєкті були підключені такі бібіотеки: SDL2/SDL2_mixer/SDL2_ttf
```
7. Показати знання архітектури ігрових рушіїв (продумати ігровий цикл, розділити логіку обробки івентів та відмальовку гри)
```
Розділена обробка вводу користувача,поведінка AI, обчислення траєкторії польоту м'яча та рендер.
```
Показати використання патернів проектування (бажано не тільки Singleton 🙂)
```
Singleton - класс GameBackend
Observer - функція game_ball->play_sound яка виконується при кожному зіткненні м'яча
```
