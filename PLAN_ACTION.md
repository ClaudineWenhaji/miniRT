# Plan d'Action - miniRT (Mandatory + Bonus) 🚀

Ce document détaille les étapes nécessaires pour réaliser un Ray Tracer complet en C, incluant les fonctionnalités obligatoires de 42 et les bonus.

---

## 🏗️ 1. Architecture et Fondations (Vecteurs)
Avant toute chose, il faut construire les outils mathématiques. Le Ray Tracing est un calcul constant de vecteurs.

### 1.1 Bibliothèque de Vecteurs (`vec3`)
Crée une série de fonctions manipulant une structure `t_vec3` ({double x, y, z}).
- **Basiques** : `v3_add`, `v3_sub`, `v3_mul`, `v3_div`.
- **Indispensables** : 
    - `v3_dot` (Produit scalaire) : `a.x*b.x + a.y*b.y + a.z*b.z`. Sert à calculer les angles.
    - `v3_cross` (Produit vectoriel) : Pour générer des vecteurs perpendiculaires (repère caméra).
    - `v3_mag` (Magnitude) : Longueur du vecteur.
    - `v3_normalize` : Rend le vecteur de longueur 1.0.

### 1.2 Structure de Données Flexible
Pour anticiper les bonus (multi-lumières, nouveaux objets), utilise des listes chaînées :
- `t_list *objects` : Une liste contenant des structures génériques `t_obj`.
- `t_list *lights` : Une liste de `t_light` (permet le bonus multi-spots).
- `t_material` : Intégrée à chaque objet pour gérer la couleur, le spéculaire (Phong), le damier ou les textures.

---

## 🖼️ 2. Infrastructure Graphique (MLX)
L'affichage doit être performant pour gérer les calculs complexes des bonus.

- **Image Buffer** : N'utilise QUE `mlx_new_image` et écris directement dans l'adresse (`mlx_get_data_addr`).
- **Color Mapping** : Crée une structure `t_color` ({double r, g, b}) avec des valeurs entre 0.0 et 1.0.
    - *Conversion* : Une fonction `color_to_int` multiplie par 255 et applique un `clamp` (max 255) avant de retourner l'entier pour la MLX.

---

## 📂 3. Parsing et Validation
Le parseur doit transformer le fichier `.rt` en tes structures de données.

- **GNL + Split** : Lit ligne par ligne.
- **Validation stricte** : 
    - Vérifie le nombre d'arguments par ligne.
    - Vérifie les plages de valeurs (0-255 pour couleurs, -1 à 1 pour vecteurs).
- **Extensibilité** : Prépare le parseur pour accepter des arguments bonus (ex: `co` pour cône, ou un paramètre supplémentaire pour le damier).

---

## 📐 4. Géométrie et Intersections
Le cœur du Ray Tracing : lancer un rayon et voir ce qu'il touche.

### 4.1 Génération de Rayon
Pour chaque pixel $(x, y)$, calcule un rayon partant de la `caméra.origin` vers un point du `viewport` (plan de projection).
- Prends en compte le **FOV** pour ajuster la distance entre la caméra et le viewport.

### 4.2 Fonctions d'Intersection
Chaque objet doit avoir sa fonction `intersect(ray, obj)` qui renvoie la distance `t` :
- **Sphère** : Équation quadratique $at^2 + bt + c = 0$.
- **Plan** : Intersection linéaire très simple.
- **Cylindre** : Équation quadratique + vérification des limites de hauteur + intersection des "caps" (disques).
- **Cône (Bonus)** : Similaire au cylindre, mais le rayon varie linéairement avec la hauteur.

---

## 💡 5. Modèle d'Éclairage (Phong & Ombres)
C'est ici que tu appliques les bonus visuels.

### 5.1 Algorithme de calcul de couleur
Pour chaque point d'impact :
1. **Lumière Ambiante** : `color = obj.color * ambient.ratio`.
2. **Pour chaque lumière dans `lights` (Bonus)** :
    - **Rayon d'ombre** : Lance un rayon vers la source. S'il touche un objet avant la lumière, ignore cette source (Shadow).
    - **Lumière Diffuse (Lambert)** : Calcule le produit scalaire entre la normale et le vecteur lumière.
    - **Lumière Spéculaire (Bonus Phong)** : Calcule le vecteur de réflexion. Si l'angle est faible avec l'œil, ajoute une tache brillante.

---

## 🎨 6. Bonus Spécifiques

### 6.1 Damier (Checkerboard)
Dans ta fonction de couleur, si `obj.has_checkerboard`, calcule une parité basée sur les coordonnées locales du point :
`if ((int)floor(x) + (int)floor(y) + (int)floor(z)) % 2 == 0` -> Couleur A sinon Couleur B.

### 6.2 Textures et Bump Map
- **UV Mapping** : Projette le point 3D en coordonnées 2D (u,v).
- **Normal Map** : Utilise la texture pour perturber légèrement le vecteur normal avant le calcul de lumière.

---

## 🚀 7. Optimisation (Optionnel mais recommandé pour les bonus)
Le Ray Tracing avec multi-lumières peut être lent.
- **Multi-threading** : Utilise `pthread` pour diviser l'image en 4 ou 8 bandes horizontales traitées en parallèle.

---

## 🔗 Ressources Utiles

### 📚 Apprendre le Ray Tracing
1. **[Ray Tracing in One Weekend](https://raytracing.github.io/)** : La "bible" pour débuter. Facile à traduire du C++ vers le C.
2. **[Scratchapixel](https://www.scratchapixel.com/)** : Explications ultra-détaillées des mathématiques (intersections, lumière, vecteurs).
3. **[The Ray Tracer Challenge](https://raytracerchallenge.com/)** : Une approche par tests (TDD) pour valider chaque étape de son moteur.
4. **[Physically Based Rendering (PBR)](https://www.pbr-book.org/)** : Très avancé, pour comprendre la physique de la lumière en profondeur.

### 🖥️ MiniLibX & Affichage
1. **[42 Docs - MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx.html)** : Documentation complète sur la gestion des images et des événements.
2. **[Aurelien Brabant - MLX Tutorial](https://aurelienbrabant.fr/blog/pixel-drawing-with-minilibx)** : Excellent guide pour comprendre le dessin de pixels et les buffers d'image.

### 📐 Mathématiques Spécifiques
1. **[Intersection Ligne-Cône (PDF)](https://www.geometrictools.com/Documentation/IntersectionLineCone.pdf)** : Pour le bonus sur les cônes.
2. **[Modèle de Phong](https://fr.wikipedia.org/wiki/Ombrage_de_Phong)** : Théorie pour le bonus de réflexion spéculaire.
3. **[Texture Mapping (UV)](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/texture-mapping)** : Pour les bonus damier et textures.
