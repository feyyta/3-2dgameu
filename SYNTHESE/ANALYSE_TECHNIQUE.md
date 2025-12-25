# ANALYSE TECHNIQUE COMPLÈTE - CUB3D

**Documentation technique détaillée du code**
**Version :** Mandatory Pure
**Date :** 25 Décembre 2025

---

## 📋 TABLE DES MATIÈRES

1. [Flow de Compilation](#1-flow-de-compilation)
2. [Structures de Données](#2-structures-de-données)
3. [Flow d'Exécution](#3-flow-dexécution)
4. [Module Parsing](#4-module-parsing)
5. [Module Raycasting](#5-module-raycasting)
6. [Module Rendering](#6-module-rendering)
7. [Module Events](#7-module-events)
8. [Algorithmes Clés](#8-algorithmes-clés)
9. [Optimisations](#9-optimisations)

---

## 1. FLOW DE COMPILATION

### 1.1 Processus de Compilation

```
make
  ↓
1. Compilation de libft
   gcc -c libft/*.c → libft.a
  ↓
2. Compilation de minilibx
   make -C minilibx-linux → libmlx.a
  ↓
3. Compilation des fichiers source
   gcc -c srcs/**/*.c → obj/**/*.o
   │
   ├── obj/check/check_args.o
   ├── obj/parsing/parse_file.o
   ├── obj/parsing/parse_colors.o
   ├── obj/parsing/parse_textures.o
   ├── obj/parsing/map_validator.o
   ├── obj/parsing/map_reader.o
   ├── obj/parsing/map_grid.o
   ├── obj/textures/load_textures.o
   ├── obj/player/init_player.o
   ├── obj/raycasting/init_ray.o
   ├── obj/rendering/render.o
   ├── obj/rendering/draw.o
   ├── obj/rendering/texture.o
   ├── obj/events/handle_input.o
   └── obj/main.o
  ↓
4. Linkage
   gcc obj/**/*.o -lmlx -lft -lXext -lX11 -lm -lz → cub3D
```

### 1.2 Dépendances de Compilation

```c
cub3d.h                    // Header principal
├── <mlx.h>               // Bibliothèque graphique
├── <stdlib.h>            // malloc, free, exit
├── <unistd.h>            // write
├── <fcntl.h>             // open
├── <stdio.h>             // printf (erreurs)
├── <math.h>              // cos, sin, fabs, floor
├── "libft.h"             // Fonctions utilitaires
├── "get_next_line.h"     // Lecture fichier ligne par ligne
└── <stdbool.h>           // bool, true, false
```

### 1.3 Flags de Compilation

```makefile
CFLAGS = -Wall -Wextra -Werror -g
# -Wall     : Active tous les warnings
# -Wextra   : Warnings supplémentaires
# -Werror   : Traite les warnings comme erreurs
# -g        : Ajoute symboles debug (pour gdb/valgrind)

MLXFLAGS = -L$(MLXDIR) -lmlx -lXext -lX11 -lm -lz
# -L        : Chemin bibliothèque
# -lmlx     : Lie avec libmlx
# -lXext    : X11 extensions
# -lX11     : X11 core
# -lm       : Math library (cos, sin)
# -lz       : Compression library (pour XPM)
```

---

## 2. STRUCTURES DE DONNÉES

### 2.1 Structure Principale : t_game

```c
typedef struct s_game
{
    void    *mlx;              // Pointeur instance MLX
    void    *win;              // Pointeur fenêtre MLX

    // Textures (4 orientations)
    t_texture_img   tex_north;
    t_texture_img   tex_south;
    t_texture_img   tex_west;
    t_texture_img   tex_east;

    // Données du jeu
    t_player    player;        // Position et direction joueur
    t_map       *map;          // Pointeur vers la map
    t_textures  *textures;     // Pointeur vers config textures

    // Buffer d'image
    void        *img;          // Image MLX
    char        *addr;         // Adresse buffer pixels
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}   t_game;
```

**Explication :**
- `mlx` et `win` : Gèrent la fenêtre graphique
- `tex_*` : Stockent les 4 textures de murs chargées
- `player` : État du joueur (position, direction, FOV)
- `map` : Grille de la map + infos
- `img` + `addr` : Buffer pour dessiner pixels avant affichage

### 2.2 Structure Texture : t_texture_img

```c
typedef struct s_texture_img
{
    void    *img;              // Pointeur image MLX
    char    *addr;             // Buffer pixels de la texture
    int     width;             // Largeur texture (px)
    int     height;            // Hauteur texture (px)
    int     bits_per_pixel;    // Profondeur couleur
    int     line_length;       // Octets par ligne
    int     endian;            // Ordre des octets
}   t_texture_img;
```

**Explication :**
- Encapsule une texture XPM chargée
- `addr` permet d'accéder directement aux pixels
- `width` et `height` pour le mapping texture→mur

### 2.3 Structure Map : t_map

```c
typedef struct s_map
{
    char    **grid;            // Grille 2D de la map
    int     width;             // Largeur (cases)
    int     height;            // Hauteur (cases)
    int     player_x;          // Position spawn X (grid)
    int     player_y;          // Position spawn Y (grid)
    char    player_dir;        // Direction initiale (N/S/E/W)
}   t_map;
```

**Explication :**
- `grid[y][x]` : '0' = vide, '1' = mur, ' ' = hors map
- `player_x/y` : Coordonnées entières du spawn
- `player_dir` : Détermine l'orientation initiale du vecteur direction

### 2.4 Structure Configuration : t_textures

```c
typedef struct s_textures
{
    char *north;               // Chemin texture nord
    char *south;               // Chemin texture sud
    char *west;                // Chemin texture ouest
    char *east;                // Chemin texture est

    int floor[3];              // Couleur sol RGB
    int ceiling[3];            // Couleur plafond RGB
}   t_textures;
```

**Explication :**
- Stocke la configuration parsée du fichier .cub
- `floor/ceiling` : Tableaux RGB [R, G, B] (0-255)

### 2.5 Structure Joueur : t_player

```c
typedef struct s_player
{
    double  pos_x;             // Position X (coordonnées monde)
    double  pos_y;             // Position Y
    double  dir_x;             // Vecteur direction X
    double  dir_y;             // Vecteur direction Y
    double  plane_x;           // Vecteur plan caméra X
    double  plane_y;           // Vecteur plan caméra Y
}   t_player;
```

**Explication mathématique :**

```
Exemple : Joueur face au Nord (N)

       plane
    (-0.66, 0)────────(0.66, 0)    ← Plan caméra (FOV)
                  │
                  │ dir (0, -1)    ← Direction regard
                  │
                  ● (pos_x, pos_y) ← Position joueur

FOV = 2 * atan(|plane| / |dir|) ≈ 66°
```

- **dir** : Vecteur unitaire de la direction du regard
- **plane** : Vecteur perpendiculaire à `dir`, définit le FOV
- **pos** : Position exacte dans la map (flottant pour mouvement fluide)

### 2.6 Structure Rayon : t_ray

```c
typedef struct s_ray
{
    // Direction du rayon
    double  ray_dir_x;
    double  ray_dir_y;

    // Position dans la grille (case actuelle testée)
    int     map_x;
    int     map_y;

    // Distances jusqu'aux prochaines bordures
    double  dist_to_bord_x;    // Distance horizontale
    double  dist_to_bord_y;    // Distance verticale

    // Deltas (distance pour traverser 1 case)
    double  delta_dist_x;
    double  delta_dist_y;

    // Direction de progression (-1 ou +1)
    int     step_direction_x;
    int     step_direction_y;

    // Résultats
    double  perp_wall_dist;    // Distance perpendiculaire au mur
    int     side;              // 0=vertical, 1=horizontal
    int     line_height;       // Hauteur du mur à l'écran (px)
    double  wall_x;            // Position exacte hit sur le mur
}   t_ray;
```

**Explication :**
- Utilisé par l'algorithme DDA pour chaque colonne de l'écran
- `delta_dist` : Distance constante pour avancer d'une case
- `dist_to_bord` : Distance variable jusqu'à la prochaine bordure
- `side` : Détermine quelle texture utiliser (N/S vs E/W)

---

## 3. FLOW D'EXÉCUTION

### 3.1 Vue d'Ensemble

```
main()
  ├─→ check_args()              // Valide arguments CLI
  ├─→ check_map()               // Parse et valide .cub
  │    ├─→ store_map_lines()    // Lit le fichier
  │    ├─→ parse_config_line()  // Parse NO/SO/WE/EA/F/C
  │    ├─→ parse_map_grid()     // Convertit map en grille
  │    └─→ validate_map_closed()// Vérifie fermeture
  ├─→ mlx_init()                // Initialise MLX
  ├─→ load_all_textures()       // Charge les 4 textures XPM
  ├─→ init_player()             // Position + direction initiales
  ├─→ mlx_new_window()          // Crée la fenêtre
  ├─→ mlx_new_image()           // Crée le buffer d'image
  ├─→ mlx_hook()                // Configure les hooks
  │    ├─→ close_window         // Croix rouge
  │    ├─→ handle_keypress      // Touches clavier
  │    └─→ render_loop          // Boucle de rendu
  └─→ mlx_loop()                // Boucle événements MLX
       │
       └─→ [Boucle infinie]
            ├─→ render_frame()   // Rendu 1 frame
            │    ├─→ Pour chaque colonne x (0→800):
            │    │    ├─→ init_ray()
            │    │    ├─→ init_ray_step()
            │    │    ├─→ algo_dda()         // Trouve mur
            │    │    ├─→ calculate_wall_distance()
            │    │    └─→ draw_column()      // Dessine colonne
            │    └─→ mlx_put_image_to_window()
            └─→ [Attend événements]
                 ├─→ Touche W/A/S/D → move_*()
                 ├─→ Flèche ← → → rotate_camera()
                 └─→ ESC → close_window()
```

### 3.2 Flux Détaillé de main()

```c
int main(int argc, char **argv)
{
    // 1. DÉCLARATION
    t_game      game;
    t_textures  textures;
    t_map       map;

    // 2. VALIDATION ET PARSING
    ft_bzero(&textures, sizeof(t_textures));

    if (check_args(argc, argv) == 0)      // Vérifie argc=2, extension .cub
        exit(EXIT_FAILURE);

    if (check_map(argc, argv, &textures, &map) == 0)  // Parse tout
        exit(EXIT_FAILURE);

    // 3. INITIALISATION MLX
    game.mlx = mlx_init();
    if (!game.mlx)
        return (1);

    // 4. CHARGEMENT ASSETS
    load_all_textures(&game, &textures);   // Charge 4 textures XPM

    // 5. INITIALISATION JOUEUR
    init_player(&game.player, &map);       // Position + direction

    // 6. SETUP GAME
    game.map = &map;
    game.textures = &textures;

    // 7. CRÉATION FENÊTRE
    game.win = mlx_new_window(game.mlx, 800, 600, "cub3D");

    // 8. CRÉATION BUFFER IMAGE
    game.img = mlx_new_image(game.mlx, 800, 600);
    game.addr = mlx_get_data_addr(game.img,
                &game.bits_per_pixel,
                &game.line_length,
                &game.endian);

    // 9. HOOKS MLX
    mlx_hook(game.win, 17, 1L<<17, close_window, &game);    // X rouge
    mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);   // Clavier
    mlx_loop_hook(game.mlx, render_loop, &game);            // Rendu

    // 10. BOUCLE PRINCIPALE
    mlx_loop(game.mlx);

    // 11. CLEANUP (jamais atteint, MLX gère l'exit)
    free_map_grid(&map);
    return (0);
}
```

---

## 4. MODULE PARSING

### 4.1 Fonction check_args()

**Fichier :** `srcs/check/check_args.c`

```c
int check_args(int argc, char **argv)
{
    int len;

    // Vérifie nombre d'arguments
    if (argc != 2)
    {
        printf("Error\nUsage: ./cub3D <map.cub>\n");
        return (0);
    }

    // Vérifie extension .cub
    len = ft_strlen(argv[1]);
    if (len < 4 || ft_strncmp(&argv[1][len - 4], ".cub", 4) != 0)
    {
        printf("Error\nMap file must have .cub extension\n");
        return (0);
    }

    return (1);
}
```

**Flow :**
1. Vérifie `argc == 2` (programme + 1 argument)
2. Vérifie que le fichier se termine par `.cub`
3. Retourne 1 (succès) ou 0 (échec)

### 4.2 Fonction check_map() - Coordinateur

**Fichier :** `srcs/parsing/parse_file.c`

```c
int check_map(int argc, char **argv, t_textures *textures, t_map *map)
{
    char    **lines;
    int     line_count;
    int     map_start;

    (void)argc;

    // 1. Initialise structure textures
    init_textures(textures);

    // 2. Lit toutes les lignes du fichier
    lines = store_map_lines(argv[1], &line_count);
    if (!lines)
        return (0);

    // 3. Trouve où commence la map dans le fichier
    map_start = find_map_start(lines, line_count, textures);

    // 4. Validation complète
    if (!validate_textures(textures) ||        // Vérifie textures définies
        map_start == -1 ||                     // Vérifie map trouvée
        !parse_map_grid(lines, map_start, map) || // Parse grille
        !validate_map_closed(map))             // Vérifie fermeture
    {
        free_map_lines(lines, line_count);
        return (0);
    }

    // 5. Nettoyage
    free_map_lines(lines, line_count);
    return (1);
}
```

### 4.3 Fonction store_map_lines()

**Fichier :** `srcs/parsing/map_reader.c`

```c
char **store_map_lines(char *filename, int *line_count)
{
    int     fd;
    int     count;
    char    **lines;
    char    *line;

    // 1. Ouvre le fichier
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error\nCannot open file: %s\n", filename);
        return (NULL);
    }

    // 2. PREMIÈRE PASSE : Compte les lignes
    count = 0;
    while (get_next_line(fd, &line) > 0)
    {
        count++;
        free(line);
    }
    close(fd);

    // 3. Allocation tableau
    lines = malloc(sizeof(char *) * (count + 1));
    if (!lines)
        return (NULL);

    // 4. DEUXIÈME PASSE : Stocke les lignes
    fd = open(filename, O_RDONLY);
    count = 0;
    while (get_next_line(fd, &line) > 0)
        lines[count++] = line;
    lines[count] = NULL;
    close(fd);

    *line_count = count;
    return (lines);
}
```

**Pourquoi deux passes ?**
- On ne peut pas allouer le tableau sans connaître le nombre de lignes
- get_next_line() ne permet pas de revenir en arrière
- Solution : lire une fois pour compter, rouvrir pour stocker

### 4.4 Fonction parse_textures()

**Fichier :** `srcs/parsing/parse_textures.c`

```c
void parse_textures(char *line, t_textures *textures)
{
    char *path_texture;

    // 1. Extrait le chemin (après les 3 premiers chars "NO ")
    path_texture = ft_strtrim(line + 3, " \t\n\r\v\f");

    if (!path_texture || !*path_texture)
    {
        printf("Error\nEmpty texture path\n");
        if (path_texture)
            free(path_texture);
        exit(EXIT_FAILURE);
    }

    // 2. Vérifie que le fichier existe
    int fd = open(path_texture, O_RDONLY);
    if (fd == -1)
    {
        printf("Error\nTexture %s not found\n", path_texture);
        free(path_texture);
        exit(EXIT_FAILURE);
    }
    close(fd);

    // 3. Stocke selon le type
    if (ft_strncmp(line, "NO ", 3) == 0)
        textures->north = path_texture;
    else if (ft_strncmp(line, "SO ", 3) == 0)
        textures->south = path_texture;
    else if (ft_strncmp(line, "WE ", 3) == 0)
        textures->west = path_texture;
    else if (ft_strncmp(line, "EA ", 3) == 0)
        textures->east = path_texture;
}
```

**Exemple :**
```
Input: "NO ./textures/north.xpm\n"
       ↓
1. ft_strtrim("./textures/north.xpm\n") → "./textures/north.xpm"
2. open("./textures/north.xpm") → fd valide
3. textures->north = "./textures/north.xpm"
```

### 4.5 Fonction parse_color()

**Fichier :** `srcs/parsing/parse_colors.c`

```c
void parse_color(char *line, int *color_array)
{
    int r, g, b;

    // Parse format "F 220,100,0" ou "C 225,30,0"
    if (sscanf(line + 2, "%d,%d,%d", &r, &g, &b) != 3)
    {
        printf("Error\nInvalid color format\n");
        exit(EXIT_FAILURE);
    }

    // Validation range RGB
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        printf("Error\nColor values must be between 0 and 255\n");
        exit(EXIT_FAILURE);
    }

    // Stocke dans le tableau
    color_array[0] = r;
    color_array[1] = g;
    color_array[2] = b;
}
```

**Exemple :**
```
Input: "F 40,35,30\n"
       ↓
sscanf(line+2, "%d,%d,%d") → r=40, g=35, b=30
       ↓
color_array[0] = 40
color_array[1] = 35
color_array[2] = 30
```

### 4.6 Fonction parse_map_grid()

**Fichier :** `srcs/parsing/map_grid.c`

```c
int parse_map_grid(char **lines, int start, t_map *map)
{
    int i;

    // 1. Init valeurs
    map->player_x = -1;
    map->player_y = -1;

    // 2. Calcule dimensions (largeur max, hauteur)
    if (!get_map_dimensions(lines, start, map))
        return (0);

    // 3. Alloue la grille rectangulaire
    if (!allocate_map_grid(map))
        return (0);

    // 4. Remplit la grille
    i = 0;
    while (i < map->height)
    {
        fill_map_row(map, lines[start + i], i);
        i++;
    }

    // 5. Vérifie qu'un joueur a été trouvé
    if (map->player_x == -1)
    {
        printf("Error\nNo player position found\n");
        return (0);
    }

    return (1);
}
```

**Détails de fill_map_row() :**

```c
static void fill_map_row(t_map *map, char *line, int y)
{
    int x;

    x = 0;
    // Copie caractère par caractère
    while (line[x] && line[x] != '\n')
    {
        // Si c'est N/S/E/W → joueur trouvé
        if (line[x] == 'N' || line[x] == 'S' ||
            line[x] == 'E' || line[x] == 'W')
        {
            if (map->player_x != -1)  // Déjà un joueur
            {
                printf("Error\nMultiple player positions\n");
                exit(EXIT_FAILURE);
            }
            map->player_x = x;
            map->player_y = y;
            map->player_dir = line[x];
            map->grid[y][x] = '0';  // Remplace par espace vide
        }
        else
            map->grid[y][x] = line[x];
        x++;
    }

    // Remplit le reste avec des espaces (map rectangulaire)
    while (x < map->width)
    {
        map->grid[y][x] = ' ';
        x++;
    }
    map->grid[y][x] = '\0';
}
```

**Pourquoi map rectangulaire ?**
```
Input (irrégulier):
    1111111
    10000001
    101
    11111111

Output (rectangulaire):
    1111111
    10000001
    101
    11111111
```
→ Simplifie l'accès `grid[y][x]` sans vérifier la longueur

### 4.7 Fonction validate_map_closed()

**Fichier :** `srcs/parsing/map_validator.c`

```c
int validate_map_closed(t_map *map)
{
    int x, y;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            // Pour chaque espace vide
            if (map->grid[y][x] == '0')
            {
                // Vérifie qu'il n'est pas en bordure
                if (!check_border(map, x, y))
                    return (0);
            }
            x++;
        }
        y++;
    }
    return (1);
}

static int check_border(t_map *map, int x, int y)
{
    // Vérifie pas sur les bords de la grille
    if (y == 0 || y == map->height - 1 ||
        x == 0 || x == map->width - 1)
    {
        printf("Error\nMap not closed at borders\n");
        return (0);
    }

    // Vérifie que les 4 voisins ne sont pas des espaces
    if (map->grid[y - 1][x] == ' ' ||  // Haut
        map->grid[y + 1][x] == ' ' ||  // Bas
        map->grid[y][x - 1] == ' ' ||  // Gauche
        map->grid[y][x + 1] == ' ')    // Droite
    {
        printf("Error\nMap not properly enclosed\n");
        return (0);
    }

    return (1);
}
```

**Logique :**
```
 11111
 1   1   ← Espace vide en bord → ERREUR
 11111

 11111
 10 01   ← Espace avec ' ' à côté → ERREUR
 11111

 11111
 10001   ← OK : entouré de '1' ou '0'
 11111
```

---

## 5. MODULE RAYCASTING

### 5.1 Fonction init_player()

**Fichier :** `srcs/player/init_player.c`

```c
void init_player(t_player *player, t_map *map)
{
    // Position = centre de la case spawn
    player->pos_x = map->player_x + 0.5;
    player->pos_y = map->player_y + 0.5;

    // Direction et plan selon orientation
    if (map->player_dir == 'N')
    {
        player->dir_x = 0;
        player->dir_y = -1;     // Haut
        player->plane_x = 0.66; // FOV horizontal
        player->plane_y = 0;
    }
    else if (map->player_dir == 'S')
    {
        player->dir_x = 0;
        player->dir_y = 1;      // Bas
        player->plane_x = -0.66;
        player->plane_y = 0;
    }
    else if (map->player_dir == 'E')
    {
        player->dir_x = 1;      // Droite
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = 0.66;
    }
    else if (map->player_dir == 'W')
    {
        player->dir_x = -1;     // Gauche
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = -0.66;
    }
}
```

**Géométrie :**

```
Nord (N):
    dir = (0, -1)    ← Regarde vers le haut
    plane = (0.66, 0) ← Plan horizontal

    plane (-0.66,0) ──────────── (0.66,0)
                      │
                      │ dir
                      ●

Sud (S):
    dir = (0, 1)     ← Regarde vers le bas
    plane = (-0.66, 0)

Est (E):
    dir = (1, 0)     ← Regarde vers la droite
    plane = (0, 0.66)

Ouest (W):
    dir = (-1, 0)    ← Regarde vers la gauche
    plane = (0, -0.66)
```

### 5.2 Fonction init_ray()

**Fichier :** `srcs/raycasting/init_ray.c`

```c
void init_ray(t_ray *ray, t_player *player, int x)
{
    double camera_x;

    // 1. Calcule coefficient caméra pour cette colonne
    //    x=0   → camera_x = -1 (bord gauche)
    //    x=400 → camera_x =  0 (centre)
    //    x=800 → camera_x =  1 (bord droit)
    camera_x = 2 * x / (double)WIN_WIDTH - 1;

    // 2. Direction du rayon = dir + plane * camera_x
    ray->ray_dir_x = player->dir_x + player->plane_x * camera_x;
    ray->ray_dir_y = player->dir_y + player->plane_y * camera_x;

    // 3. Case de départ
    ray->map_x = (int)player->pos_x;
    ray->map_y = (int)player->pos_y;

    // 4. Distance pour traverser 1 case complète
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}
```

**Mathématiques :**

```
Exemple: Joueur en (5.5, 5.5), dir=(0,-1), plane=(0.66,0)

Colonne x=0 (bord gauche écran):
  camera_x = -1
  ray_dir = (0,-1) + (0.66,0)*(-1) = (-0.66, -1)
           ↑ dir    ↑ plane        ↑ rayon gauche

Colonne x=400 (centre écran):
  camera_x = 0
  ray_dir = (0,-1) + (0.66,0)*(0) = (0, -1)
           ↑ exactement la direction du joueur

Colonne x=800 (bord droit écran):
  camera_x = 1
  ray_dir = (0,-1) + (0.66,0)*(1) = (0.66, -1)
           ↑ rayon droite
```

**Delta distance :**
```
Si ray_dir_x = 0.8:
  delta_dist_x = |1 / 0.8| = 1.25

Signification: Pour avancer de 1 unité en X,
                le rayon parcourt 1.25 unités au total
```

### 5.3 Fonction init_ray_step()

**Fichier :** `srcs/raycasting/init_ray.c`

```c
void init_ray_step(t_ray *ray, t_player *player)
{
    // Direction X
    if (ray->ray_dir_x < 0)
    {
        ray->step_direction_x = -1;  // Va vers la gauche
        ray->dist_to_bord_x = (player->pos_x - ray->map_x)
                              * ray->delta_dist_x;
    }
    else
    {
        ray->step_direction_x = 1;   // Va vers la droite
        ray->dist_to_bord_x = (ray->map_x + 1.0 - player->pos_x)
                              * ray->delta_dist_x;
    }

    // Direction Y (idem)
    if (ray->ray_dir_y < 0)
    {
        ray->step_direction_y = -1;
        ray->dist_to_bord_y = (player->pos_y - ray->map_y)
                              * ray->delta_dist_y;
    }
    else
    {
        ray->step_direction_y = 1;
        ray->dist_to_bord_y = (ray->map_y + 1.0 - player->pos_y)
                              * ray->delta_dist_y;
    }
}
```

**Explication visuelle :**

```
Joueur en (5.7, 5.3), rayon vers ↗ (dir_x>0, dir_y<0)

┌─────┬─────┬─────┐
│ 5,4 │ 6,4 │ 7,4 │
├─────┼─────┼─────┤
│ 5,5 │ 6,5 │ 7,5 │  ● = joueur (5.7, 5.3)
├─────┼─────┼─────┤     → ray va vers (6,4)
│ 5,6 │ 6,6 │ 7,6 │
└─────┴─────┴─────┘

map_x = 5, map_y = 5

step_direction_x = 1  (va vers 6)
step_direction_y = -1 (va vers 4)

dist_to_bord_x = (6.0 - 5.7) * delta = 0.3 * delta
dist_to_bord_y = (5.3 - 5.0) * delta = 0.3 * delta
                 ↑ distance à parcourir jusqu'à la bordure
```

### 5.4 Fonction algo_dda() - CŒUR DU RAYCASTING

**Fichier :** `srcs/raycasting/init_ray.c`

```c
void algo_dda(t_ray *ray, t_map *map)
{
    int hit;

    hit = 0;
    while (hit == 0)
    {
        // Compare les distances : quelle bordure est la plus proche ?
        if (ray->dist_to_bord_x < ray->dist_to_bord_y)
        {
            // Bordure verticale (X) plus proche
            ray->dist_to_bord_x += ray->delta_dist_x;  // Avance
            ray->map_x += ray->step_direction_x;       // Change de case
            ray->side = 0;                              // Mur vertical
        }
        else
        {
            // Bordure horizontale (Y) plus proche
            ray->dist_to_bord_y += ray->delta_dist_y;
            ray->map_y += ray->step_direction_y;
            ray->side = 1;                              // Mur horizontal
        }

        // Vérifie si on a touché un mur
        if (map->grid[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
}
```

**Animation DDA :**

```
Étape 0: Joueur en (5.5, 5.5)
         map_x=5, map_y=5
         dist_x=0.5, dist_y=0.3

┌───┬───┬───┐
│   │   │   │
├───┼───┼───┤
│   │ ● │   │  ← Joueur (5,5)
├───┼───┼───┤
│   │   │ 1 │
└───┴───┴───┘

Étape 1: dist_y < dist_x → Avance en Y
         map_y = 6
         dist_y += delta_y

┌───┬───┬───┐
│   │   │   │
├───┼───┼───┤
│   │   │   │
├───┼───┼───┤
│   │ ● │ 1 │  ← Rayon en (5,6)
└───┴───┴───┘
         grid[6][5] = '0' → continue

Étape 2: dist_x < dist_y → Avance en X
         map_x = 6
         dist_x += delta_x

┌───┬───┬───┐
│   │   │   │
├───┼───┼───┤
│   │   │   │
├───┼───┼───┤
│   │   │ ● │  ← Rayon en (6,6)
└───┴───┴───┘
         grid[6][6] = '1' → HIT ! side=0
```

**Pourquoi DDA est rapide :**
- Pas de calcul de racine carrée
- Seulement des additions et comparaisons
- Teste uniquement les cases traversées (pas toute la map)

### 5.5 Fonction calculate_wall_distance()

**Fichier :** `srcs/raycasting/init_ray.c`

```c
void calculate_wall_distance(t_ray *ray, t_player *player)
{
    // 1. Distance perpendiculaire (évite fisheye)
    if (ray->side == 0)  // Mur vertical (N/S)
        ray->perp_wall_dist = (ray->map_x - player->pos_x
                               + (1 - ray->step_direction_x) / 2)
                              / ray->ray_dir_x;
    else                 // Mur horizontal (E/W)
        ray->perp_wall_dist = (ray->map_y - player->pos_y
                               + (1 - ray->step_direction_y) / 2)
                              / ray->ray_dir_y;

    // 2. Hauteur du mur à l'écran
    ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);

    // 3. Position exacte du hit sur le mur (pour texture)
    if (ray->side == 0)
        ray->wall_x = player->pos_y
                      + ray->perp_wall_dist * ray->ray_dir_y;
    else
        ray->wall_x = player->pos_x
                      + ray->perp_wall_dist * ray->ray_dir_x;

    ray->wall_x -= floor(ray->wall_x);  // Partie fractionnaire [0, 1)
}
```

**Distance perpendiculaire vs euclidienne :**

```
Sans correction (distance euclidienne):
                ╱
        rayon  ╱
              ╱  d_eucl
             ╱
            ╱
           ●──────┼─────
          joueur  │
                  │ d_perp
                  │
                 mur

Effet fisheye: Les bords de l'écran semblent plus loin
→ Murs arrondis, distorsion

Avec distance perpendiculaire:
Tous les rayons mesurent la distance ⊥ au plan caméra
→ Murs droits, pas de distorsion
```

**Calcul de wall_x :**

```
Mur vertical à x=7:
  Rayon hit le mur à y = player_y + dist * ray_dir_y

  Si player_y=5.3, dist=2.5, ray_dir_y=0.8:
    wall_x = 5.3 + 2.5*0.8 = 7.3
    wall_x -= floor(7.3) = 0.3

  → On a touché le mur à 30% de sa largeur
  → On utilisera le pixel texture[tex_width * 0.3][tex_y]
```

---

## 6. MODULE RENDERING

### 6.1 Fonction render_loop()

**Fichier :** `srcs/rendering/render.c`

```c
int render_loop(t_game *game)
{
    // Appelé en boucle par MLX (≈60 FPS)
    render_frame(game, game->textures, game->map);
    return (0);
}
```

### 6.2 Fonction render_frame()

**Fichier :** `srcs/rendering/render.c`

```c
void render_frame(t_game *game, t_textures *textures, t_map *map)
{
    t_ray   ray;
    int     x;

    // Pour chaque colonne de l'écran (800 colonnes)
    x = 0;
    while (x < WIN_WIDTH)
    {
        // 1. Lance un rayon pour cette colonne
        init_ray(&ray, &game->player, x);
        init_ray_step(&ray, &game->player);

        // 2. Trouve le mur
        algo_dda(&ray, map);

        // 3. Calcule la distance et hauteur
        calculate_wall_distance(&ray, &game->player);

        // 4. Dessine la colonne (sol + mur + plafond)
        draw_column(game, &ray, textures, x);

        x++;
    }

    // 5. Affiche l'image complète à l'écran
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
```

**Pourquoi colonne par colonne ?**
```
Écran 800x600:

x=0   x=1   x=2  ...  x=799
 │     │     │          │
 │     │     │          │
 │ ray │ ray │          │ ray
 │  ↑  │  ↑  │          │  ↑
 ●──────────────────────────  ← Joueur
    800 rayons lancés
```

Chaque rayon détermine :
- La hauteur du mur pour cette colonne
- Quelle texture utiliser
- Quelle partie de la texture afficher

### 6.3 Fonction draw_column()

**Fichier :** `srcs/rendering/draw.c`

```c
void draw_column(t_game *game, t_ray *ray, t_textures *textures, int x)
{
    int start;
    int end;

    // 1. Calcule où commence et finit le mur à l'écran
    calculate_draw_limits(ray, &start, &end);

    // 2. Dessine le plafond (du haut jusqu'au mur)
    draw_vertical_line(game, x, 0, start,
                       rgb_to_int(textures->ceiling));

    // 3. Dessine le mur texturé
    draw_textured_wall(game, ray, x, start, end);

    // 4. Dessine le sol (du mur jusqu'au bas)
    draw_vertical_line(game, x, end, WIN_HEIGHT - 1,
                       rgb_to_int(textures->floor));
}
```

**Schéma :**

```
y=0   ┌─────┐
      │█████│  ← Plafond (ceiling color)
      │█████│
start │─────│
      │░░░░░│  ← Mur (texture)
      │░░░░░│
      │░░░░░│
end   │─────│
      │█████│  ← Sol (floor color)
y=600 └─────┘
```

### 6.4 Fonction calculate_draw_limits()

**Fichier :** `srcs/rendering/draw.c`

```c
void calculate_draw_limits(t_ray *ray, int *start, int *end)
{
    int line_height = ray->line_height;

    // Position de départ : centre écran - moitié hauteur mur
    *start = -line_height / 2 + WIN_HEIGHT / 2;

    // Position de fin : centre écran + moitié hauteur mur
    *end = line_height / 2 + WIN_HEIGHT / 2;

    // Clamp dans les limites de l'écran
    if (*start < 0)
        *start = 0;
    if (*end >= WIN_HEIGHT)
        *end = WIN_HEIGHT - 1;
}
```

**Exemple :**

```
Mur à distance 2.0:
  line_height = 600 / 2.0 = 300 pixels

  start = -300/2 + 600/2 = -150 + 300 = 150
  end   = 300/2 + 600/2  = 150 + 300 = 450

  → Mur affiché de y=150 à y=450 (300px de haut)
  → Centré verticalement

Mur à distance 1.0:
  line_height = 600 / 1.0 = 600 pixels

  start = -600/2 + 600/2 = 0
  end   = 600/2 + 600/2  = 600 → clamped à 599

  → Mur remplit tout l'écran
```

### 6.5 Fonction draw_textured_wall()

**Fichier :** `srcs/rendering/texture.c`

```c
void draw_textured_wall(t_game *game, t_ray *ray, int x,
                        int start, int end)
{
    t_texture_img   *tex;
    int             tex_x;
    int             tex_y;
    int             y;
    double          step;
    double          tex_pos;

    // 1. Sélectionne la texture selon orientation
    tex = select_texture(game, ray);

    // 2. Calcule colonne de texture (0 → tex_width)
    tex_x = (int)(ray->wall_x * (double)tex->width);

    // 3. Inverse si nécessaire (direction du rayon)
    if ((ray->side == 0 && ray->step_direction_x < 0) ||
        (ray->side == 1 && ray->step_direction_y > 0))
        tex_x = tex->width - tex_x - 1;

    // 4. Calcule step (combien avancer dans texture par pixel écran)
    step = 1.0 * tex->height / ray->line_height;

    // 5. Position de départ dans la texture
    tex_pos = (start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;

    // 6. Dessine pixel par pixel
    y = start;
    while (y <= end)
    {
        // Ligne de texture (modulo pour éviter overflow)
        tex_y = (int)tex_pos & (tex->height - 1);

        // Avance dans la texture
        tex_pos += step;

        // Récupère et affiche le pixel
        put_pixel(game, x, y, get_texture_color(tex, tex_x, tex_y));

        y++;
    }
}
```

**Mapping texture → écran :**

```
Texture 64x64          Mur à l'écran (300px haut)

(tex_x, 0)────         y=150 ─────
    │                      │
    │  64px                │  300px
    │                      │
(tex_x, 64)───         y=450 ─────

step = 64 / 300 = 0.213

Pour chaque y de 150 à 450:
  tex_y = (int)tex_pos
  tex_pos += 0.213

  → Interpole la texture sur la hauteur du mur
```

### 6.6 Fonction select_texture()

**Fichier :** `srcs/rendering/texture.c`

```c
static t_texture_img *select_texture(t_game *game, t_ray *ray)
{
    if (ray->side == 0)      // Mur vertical (N/S)
    {
        if (ray->step_direction_x > 0)
            return (&game->tex_east);   // Regarde vers l'Est
        else
            return (&game->tex_west);   // Regarde vers l'Ouest
    }
    else                     // Mur horizontal (E/W)
    {
        if (ray->step_direction_y > 0)
            return (&game->tex_south);  // Regarde vers le Sud
        else
            return (&game->tex_north);  // Regarde vers le Nord
    }
}
```

**Logique :**

```
Mur vertical (side=0):
  ┃ ← Mur
  ┃

  Si rayon vient de ←  (step_x > 0) → texture EAST
  Si rayon vient de →  (step_x < 0) → texture WEST

Mur horizontal (side=1):
  ═══ ← Mur

  Si rayon vient de ↑  (step_y > 0) → texture SOUTH
  Si rayon vient de ↓  (step_y < 0) → texture NORTH
```

### 6.7 Fonction put_pixel()

**Fichier :** `srcs/rendering/draw.c`

```c
void put_pixel(t_game *game, int x, int y, int color)
{
    char *dst;

    // Vérifie que le pixel est dans l'écran
    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;

    // Calcule l'adresse du pixel dans le buffer
    dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));

    // Écrit la couleur (casting en int*)
    *(unsigned int*)dst = color;
}
```

**Explication buffer MLX :**

```
Buffer image MLX = tableau 1D de bytes

Écran 800x600, 32 bits/pixel (4 bytes):

Pixel (x=10, y=5):
  offset = 5 * line_length + 10 * 4
         = 5 * 3200 + 40
         = 16040 bytes depuis le début

  addr[16040..16043] = color (4 bytes)
```

### 6.8 Fonction get_texture_color()

**Fichier :** `srcs/rendering/texture.c`

```c
int get_texture_color(t_texture_img *tex, int tex_x, int tex_y)
{
    char *pixel;

    // Calcule adresse du pixel dans la texture
    pixel = tex->addr + (tex_y * tex->line_length
                         + tex_x * (tex->bits_per_pixel / 8));

    // Retourne la couleur
    return (*(unsigned int*)pixel);
}
```

---

## 7. MODULE EVENTS

### 7.1 Fonction handle_keypress()

**Fichier :** `srcs/events/handle_input.c`

```c
int handle_keypress(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)           // 65307
        close_window(game);
    else if (keycode == KEY_W)        // 119
        move_forward_backward(&game->player, game->map, 1);
    else if (keycode == KEY_S)        // 115
        move_forward_backward(&game->player, game->map, 0);
    else if (keycode == KEY_A)        // 97
        move_left_right(&game->player, game->map, 0);
    else if (keycode == KEY_D)        // 100
        move_left_right(&game->player, game->map, 1);
    else if (keycode == KEY_LEFT)     // 65361
        rotate_camera(&game->player, 0);
    else if (keycode == KEY_RIGHT)    // 65363
        rotate_camera(&game->player, 1);

    return (0);
}
```

### 7.2 Fonction move_forward_backward()

**Fichier :** `srcs/events/handle_input.c`

```c
static void move_forward_backward(t_player *player, t_map *map, int forward)
{
    double new_x;
    double new_y;

    // Calcule nouvelle position
    if (forward)
    {
        new_x = player->pos_x + player->dir_x * MOVE_SPEED;
        new_y = player->pos_y + player->dir_y * MOVE_SPEED;
    }
    else  // backward
    {
        new_x = player->pos_x - player->dir_x * MOVE_SPEED;
        new_y = player->pos_y - player->dir_y * MOVE_SPEED;
    }

    // Applique si pas de collision
    if (is_valid_position(map, (int)new_x, (int)new_y))
    {
        player->pos_x = new_x;
        player->pos_y = new_y;
    }
}
```

**Explication :**

```
MOVE_SPEED = 0.1

Joueur en (5.5, 5.5), dir = (0, -1)  [Nord]

Touche W (forward):
  new_pos = (5.5, 5.5) + (0, -1) * 0.1
          = (5.5, 5.4)

Touche S (backward):
  new_pos = (5.5, 5.5) - (0, -1) * 0.1
          = (5.5, 5.6)
```

### 7.3 Fonction move_left_right()

**Fichier :** `srcs/events/handle_input.c`

```c
static void move_left_right(t_player *player, t_map *map, int right)
{
    double new_x;
    double new_y;

    // Strafe = déplacement perpendiculaire (utilise plane)
    if (right)
    {
        new_x = player->pos_x + player->plane_x * MOVE_SPEED;
        new_y = player->pos_y + player->plane_y * MOVE_SPEED;
    }
    else  // left
    {
        new_x = player->pos_x - player->plane_x * MOVE_SPEED;
        new_y = player->pos_y - player->plane_y * MOVE_SPEED;
    }

    if (is_valid_position(map, (int)new_x, (int)new_y))
    {
        player->pos_x = new_x;
        player->pos_y = new_y;
    }
}
```

**Pourquoi utiliser plane ?**

```
dir = (0, -1)    [Nord]
plane = (0.66, 0) [Perpendiculaire]

Touche A (strafe gauche):
  new_pos = pos - plane * 0.1
          = (5.5, 5.5) - (0.66, 0) * 0.1
          = (5.434, 5.5)
          ↑ se déplace vers la gauche

Touche D (strafe droite):
  new_pos = pos + plane * 0.1
          = (5.5, 5.5) + (0.66, 0) * 0.1
          = (5.566, 5.5)
          ↑ se déplace vers la droite
```

### 7.4 Fonction rotate_camera()

**Fichier :** `srcs/events/handle_input.c`

```c
static void rotate_camera(t_player *player, int right)
{
    double old_dir_x;
    double old_plane_x;
    double rot_speed;

    rot_speed = ROT_SPEED;  // 0.05 radians
    if (!right)
        rot_speed = -rot_speed;

    // Rotation de dir
    old_dir_x = player->dir_x;
    player->dir_x = player->dir_x * cos(rot_speed)
                    - player->dir_y * sin(rot_speed);
    player->dir_y = old_dir_x * sin(rot_speed)
                    + player->dir_y * cos(rot_speed);

    // Rotation de plane (même angle)
    old_plane_x = player->plane_x;
    player->plane_x = player->plane_x * cos(rot_speed)
                      - player->plane_y * sin(rot_speed);
    player->plane_y = old_plane_x * sin(rot_speed)
                      + player->plane_y * cos(rot_speed);
}
```

**Matrice de rotation 2D :**

```
Rotation d'un vecteur (x, y) de θ radians:

┌ x' ┐   ┌ cos(θ)  -sin(θ) ┐ ┌ x ┐
│    │ = │                  │ │   │
└ y' ┘   └ sin(θ)   cos(θ) ┘ └ y ┘

x' = x * cos(θ) - y * sin(θ)
y' = x * sin(θ) + y * cos(θ)
```

**Exemple :**

```
θ = 0.05 rad ≈ 2.86°

dir = (0, -1)  [Nord]

Après rotation droite:
  new_dir_x = 0 * cos(0.05) - (-1) * sin(0.05)
            = 0.0499
  new_dir_y = 0 * sin(0.05) + (-1) * cos(0.05)
            = -0.9987

  → Légère rotation vers la droite
```

### 7.5 Fonction is_valid_position()

**Fichier :** `srcs/events/handle_input.c`

```c
static int is_valid_position(t_map *map, int x, int y)
{
    // Vérifie pas un mur
    if (map->grid[y][x] == '1')
        return (0);

    return (1);
}
```

**Simple mais efficace :**
- Convertit position flottante en coordonnées grille
- Check si la case est traversable
- Empêche de traverser les murs

---

## 8. ALGORITHMES CLÉS

### 8.1 Algorithme DDA (Digital Differential Analyzer)

**Concept :** Traverser une grille en suivant une ligne droite

```
Pseudocode:

1. Partir de la position joueur
2. Calculer delta (distance pour traverser 1 case)
3. Boucle:
   a. Comparer dist_x et dist_y
   b. Avancer dans la direction la plus proche
   c. Tester si mur
   d. Si mur → stop, sinon continuer
```

**Complexité :** O(distance), très efficace

**Avantages :**
- Pas de calcul trigonométrique
- Teste uniquement les cases traversées
- Très rapide (additions et comparaisons)

### 8.2 Correction Fisheye

**Problème :** Distance euclidienne crée une distorsion

```
Sans correction:
  Rayons des bords semblent plus longs
  → Murs courbés

Solution:
  Utiliser distance perpendiculaire au plan caméra

  dist_perp = dist_eucl * cos(angle_rayon)
```

**Implémentation :**
```c
if (side == 0)
    perp_dist = (map_x - pos_x + correction) / ray_dir_x;
else
    perp_dist = (map_y - pos_y + correction) / ray_dir_y;
```

### 8.3 Mapping Texture

**Problème :** Plaquer une texture 2D sur un mur vertical

```
Texture 64x64        →    Mur 300px haut

1. Calculer tex_x (colonne):
   tex_x = wall_x * tex_width

2. Calculer step (ratio hauteur):
   step = tex_height / line_height

3. Pour chaque pixel y:
   tex_y = (int)tex_pos
   tex_pos += step
   color = texture[tex_x][tex_y]
```

**Optimisation :** Bitwise AND au lieu de modulo
```c
tex_y = (int)tex_pos & (tex->height - 1);
// Équivalent à: tex_y = (int)tex_pos % tex->height
// Mais plus rapide si tex->height est puissance de 2
```

---

## 9. OPTIMISATIONS

### 9.1 Buffer d'Image MLX

**Problème :** Dessiner pixel par pixel est lent

```c
// LENT (800*600 = 480000 appels MLX)
for (y = 0; y < 600; y++)
    for (x = 0; x < 800; x++)
        mlx_pixel_put(mlx, win, x, y, color);

// RAPIDE (1 seul appel)
for (y = 0; y < 600; y++)
    for (x = 0; x < 800; x++)
        buffer[y][x] = color;
mlx_put_image_to_window(mlx, win, img, 0, 0);
```

**Gain :** ×100 à ×1000 plus rapide

### 9.2 Précalcul des Deltas

```c
// Calculé 1 fois par rayon
delta_dist_x = fabs(1 / ray_dir_x);
delta_dist_y = fabs(1 / ray_dir_y);

// Réutilisé dans la boucle DDA
dist_to_bord_x += delta_dist_x;  // Addition simple
```

**Évite :** Calculs de distance à chaque itération

### 9.3 Bitwise AND pour Modulo

```c
// Si tex->height = 64 (puissance de 2)
tex_y = (int)tex_pos & 63;  // 63 = 0b111111

// Équivalent à:
tex_y = (int)tex_pos % 64;

// Mais bitwise AND est ~5× plus rapide
```

### 9.4 Clipping Précoce

```c
void calculate_draw_limits(t_ray *ray, int *start, int *end)
{
    *start = -ray->line_height / 2 + WIN_HEIGHT / 2;
    *end = ray->line_height / 2 + WIN_HEIGHT / 2;

    // Clip immédiatement
    if (*start < 0)
        *start = 0;
    if (*end >= WIN_HEIGHT)
        *end = WIN_HEIGHT - 1;
}
```

**Évite :** Dessiner des pixels hors écran

---

## 📊 PERFORMANCES ATTENDUES

### Complexité par Frame

```
Rendu 1 frame:
  800 colonnes × (
    DDA: O(distance moyenne)  ≈ 10 itérations
    + Texture: O(hauteur mur) ≈ 300 pixels
  )

Total: ~800 × 310 = 248,000 opérations

À 60 FPS: ~15 millions opérations/seconde
→ Facilement gérable par CPU moderne
```

### Mémoire Utilisée

```
Structures:
  t_game:    ~200 bytes
  t_map:     ~100 bytes + grid
  t_player:  ~50 bytes

Textures (64x64, 4 murs):
  4 × 64 × 64 × 4 bytes = 64 KB

Buffer image (800×600):
  800 × 600 × 4 bytes = 1.92 MB

Total: ~2 MB (très léger)
```

### Optimisations Possibles

1. **Multithreading** - Rendu de colonnes en parallèle
2. **Z-buffer** - Pour ajouter sprites (pas implémenté ici)
3. **Frustum culling** - Ne pas traiter ce qui est derrière
4. **LOD** - Textures moins détaillées au loin

---

**FIN DE L'ANALYSE TECHNIQUE**

*Ce document explique le fonctionnement complet du code dans l'ordre de compilation et d'exécution.*

*Pour la TODO list et les corrections à faire, voir `SYNTHESE_PROJET.md`*
