# Synthèse des Modèles d'Éclairage en Raytracing

## 1. Introduction
Dans le développement d'un moteur de rendu (Raytracer), l'éclairage simule l'interaction de la lumière avec les surfaces. Pour manipuler correctement les couleurs, il est crucial de distinguer trois concepts fondamentaux.

---

## 2. Définition des Concepts Fondamentaux

### A. L'Intensité (Le "Combien")
C'est une valeur **scalaire** (un simple nombre, souvent entre 0.0 et 1.0).
*   **Définition :** Elle représente la *quantité* pure de lumière (le flux de photons) qui atteint un point de la surface.
*   **Dépendance :** Elle varie selon la puissance de la lampe (brightness/ratio) et l'angle d'incidence (Modèle de Lambert).
*   **Analogie :** C'est le bouton de réglage de la puissance d'un projecteur.

### B. La Couleur (Le "De quelle teinte")
C'est un vecteur de 3 composantes spectrales **(Rouge, Vert, Bleu)**.
*   **Définition :** Elle représente la *qualité* de la lumière (sa longueur d'onde prédominante).
*   **Usage :** On utilise des valeurs normalisées (0.0 à 1.0) pour les calculs mathématiques.
*   **Analogie :** C'est le filtre de couleur (gélatine) que l'on place devant le projecteur.

### C. La Contribution (Le "Résultat Lumineux")
C'est un vecteur **RGB** résultant de la combinaison de l'intensité et de la couleur.
*   **Formule :** $\vec{Contribution} = Intensité \times \vec{Couleur_{Lumière}}$
*   **Définition :** C'est la lumière colorée réelle qui éclaire effectivement un point donné. Une intensité de 0.5 avec une lumière rouge donnera une contribution "rouge sombre".

---

## 3. Le Modèle de Lambert (Réflexion Diffuse)
Simule les surfaces mates. La lumière est réfléchie de manière égale dans toutes les directions.

### Calcul de l'Intensité Diffuse :
L'intensité dépend de l'angle entre la **Normale (N)** de la surface et la **Direction de la Lumière (L)**.
$$I_{diffuse} = \max(0, N \cdot L) \times \text{Luminosité\_Lampe}$$

---

## 4. Le Modèle de Phong (Réflexion Spéculaire)
Ajoute la brillance (le reflet spéculaire) dépendant de la position de l'observateur.

### Calcul de l'Intensité Spéculaire :
On calcule le vecteur de réflexion **R** de la lumière sur la surface, et son alignement avec le vecteur de vue **V** (vers la caméra).
$$R = 2(N \cdot L)N - L$$
$$I_{speculaire} = (R \cdot V)^n$$
- **n (Shininess) :** Définit la netteté du reflet (ex: 100 pour du métal, 10 pour du plastique).

---

## 5. Gestion de plusieurs lumières colorées
Le rendu final d'un pixel est l'interaction entre la couleur propre de l'objet et la somme des contributions de toutes les lumières.

### Équation Cumulative (par canal, ex: Rouge) :
Pour un point donné, on additionne toutes les **contributions** (Ambiantes et Diffuses) avant de multiplier par la couleur de l'objet.

$$R_{pixel} = R_{objet} \times \sum_{i} ( \text{Contribution\_Rouge}_i )$$

### Pourquoi multiplier ?
Multiplier la couleur de l'objet par la contribution lumineuse simule la **réflexion physique** : l'objet ne peut refléter que les couleurs qu'il possède déjà. Un objet pur Bleu ($R=0$) multiplié par une contribution Rouge donnera un pixel noir ($0 \times 1 = 0$), car le bleu absorbe le rouge.

---

## 6. Résumé Visuel
*   **Intensité :** Donne le **volume** (zones claires vs zones sombres).
*   **Couleur :** Donne l'**ambiance** (teinte de la scène).
*   **Contribution :** C'est la **lumière incidente** finale qui frappe l'objet.
*   **Couleur Objet :** Définit comment l'objet **réagit** à la lumière reçue.
