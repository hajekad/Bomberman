## Zadani semestralni prace z Progtestu
Klasická hra Bomberman

Implementujte následující varianty:

pro alespoň 2 hráče na jednom počítači
pro hru proti počítači
Hra musí splňovat následující funkcionality:

Načítání herních levelů (mapy) ze souboru (vytvořte vhodný formát)
Sbírání konfigurovatelných bonusů (zvětšení plamenu, více bomb, odpalování bomb na dálku,...)
Ukládání nejlepšího dosaženého skóre do souboru
Kde lze využít polymorfismus? (doporučené)

Ovládání hráčů: lokální hráč, umělá inteligence (různé druhy), síťový hráč
Uživatelské rozhraní: konzolové, ncurses, SDL, OpenGL (různé druhy),...
Efekty bonusů a nemocí: zvětšení plamenu, zvýšení počtu bomb,...
Další informace

https://en.wikipedia.org/wiki/Bomberman

## Specifikace zadání
Budu vytvářet hru založenou na myšlence japonské hry Bakudan Otoko s režimy singleplayer a local
    multiplayer. Oproti puvodní hře se bude v mé verzi implementován systém nemocí, které budou 
    přenosné mezi všemi charaktery ve hře. Dále budu mít ruzne typy zbraní, s tím že primární zustane
    bomba.
    Hraci si na zacatku hry mohou vybrat jakým utf-8 znakem chtějí být reprezentováni.

Level:
    Paleta[ 📦, 🚪, 🧱 , ⛩, ■ ]
    Charaktery[ 🧜, 🦸‍♂️, 🦹‍♂️, 🧚‍♀️, 🤺, 👩‍🦯 ]
    Eneme[ 🧟, 🧟‍♂️, 🧟‍♀️, 🦄, 🥵, 🤱, 🤰 ]
    Npc[]
    
    '''
    ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
    ■ 🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱⛩🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱■
    ■ 🧱      👩‍🦯          📦    📦🤱📦          📦   📦         🧱■             
    ■ 🧱  🧱📦🧱  🧱  🧱📦🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱   🧱■
    ■ 🧱📦                          📦    📦   📦               🧱■     
    ■ 🧱🧱  🧱  🧱📦🧱  🧱📦🧱  🧱  🧱  🧱  🧱  🧱  🧱🥵🧱  🧱 🧱■
    ■ 🧱  📦              📦📦      📦         📦               🧱■         
    ■ 🧱  🧱  🧱📦🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱   🧱■
    ■ 🧱    📦          📦          📦       📦        📦       🧱■
    ■ 🧱🧱  🧱🧟‍♂️🧱  🧱  🧱🥵🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱  🧱 🧱■
    ■ 🧱        📦            📦    📦      📦         📦       🧱■
    ■ 🧱  🧱  🧱  🧱📦🧱  🧱  🧱📦🧱  🧱  🧱  🧱  🧱  🧱  🧱   🧱■
    ■ 🧱    📦          📦🧟‍♂️📦        📦        📦       📦     🧱■                                                           
    ■ 🧱🧱  🧱📦🧱  🧱  🧱  🧱📦🧱📦🧱  🧱  🧱  🧱  🧱  🧱  🧱 🧱■
    ■ 🧱  📦      📦                                 🦄         🧱■
    ■ 🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🚪🧱🧱🧱🧱🧱■
    ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
    '''
Třídy:
    Viz UML class diagram...

Polymorfysmus:
    Využije se pro parent CCharacter a childy CEnemy, CPlayer a CNpc.
    Společné metody childu budou například move - kdy se charakter posune o 1 pozici do zadaného směru
                                           -perish() - smrt charaktera
