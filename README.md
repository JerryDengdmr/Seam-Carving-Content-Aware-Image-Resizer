# Seam-Carving-Content-Aware-Image-Resizer

A content-aware image resizing program built for EECS 280 at UMich. It implements the seam carving algorithm — computing pixel energy via squared color differences, building a dynamic programming cost matrix, then iteratively finding and removing minimal-cost vertical seams to shrink images. The project is built in a C-style procedural paradigm using structs as ADTs, raw pointers for pass-by-reference, 1D vectors with manual row/col indexing, PPM file I/O via streams, and function overloading (e.g. Matrix_at for const/non-const).
