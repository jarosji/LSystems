==== Zapnutí projektu ====
Doporučuji přepnout konfiguraci z "Debug" na "Release" - Aplikace bude o dost rychlejší.
U generování LSystému lze zapnout threadování (defaultně je vypuntý), ale je možné, že se objeví menší chybky - Threading lze zapnout v souboru Application/Application.h
na řádce 11 přepsat "#define ASYNC 0;" na "#define ASYNC 1;"

==== levely ====
Aplikace má 3 levely:
	1. LSystemLevel (defaultní) - Lze nastavit osvětlení scény na objektu "DirectionalLight", s kterým lze celou scénu více osvětlit.
	2. Playground - vytvoří 1000 LSystému (může být dost náročný, takže doporučuji mít zapnutý threading/release)
	3. EmptyLevel - Neobsahuje žádné objekty
Pokud by některý level měl nízké FPS, lze v souboru Application/Application.cpp na řádce 43 změnit defaultní level. Stačí přepsat "LSystemLevel" na "EmptyLevel". (V GUI lze levely také měnit)

==== Ovládání ====
[WASD] - Pohyb
[E], [Q] - Nahore/dolů
[Delete] - Odstraní vybraný objekt
Držení pravého tlačítka myši - rozhlížení
Scroll na myši - Mění rychlost kamery


==== LSystémy ====

== GUI ==
1. Horní panel obsahuje tlačítka pro vytvoření různých typů objektů do scény
2. Při zvolení LSystému z hierarchie jsou k dispozici 4 presety, které vytvoří určity LSystém
3. Tabulka "Rules" obsahuje pravidla, která se používají na zvoleném LSystému
4. Pro přidání pravidla slouží inputy, které se nacházejí hned pod tabulkou s pravidly. Příklad:
	První input: F
	Druhý input: FF-F-F-F-FF
5. input "iterations" slouží pro navolení počtu iterací (pozor při navolení větších hodnot: Bez threadingu se aplikace zasekne a při větších LSystémech je možné i přetečení bufferů a crashnutí aplikace.)

(GUI má možnost "dockingu", je tak možné přemístit jednotlivé panely)

== Akceptované turtle commandy ==
[F]
[+]
[-]
[&]
[^]
[\\]
[/]
Vysvětlivky na stránce: https://www.houdinikitchen.net/wp-content/uploads/2019/12/L-systems.pdf
