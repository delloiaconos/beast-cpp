# BEAST M4 class templates

This directory contains the M4 templates used to generate skeleton BEAST
`CellModel` and `Estimator` classes.

The templates are intentionally kept separate from the two generator scripts so
that project-wide class conventions can be changed in one place.

Use the top-level Makefile:

```bash
make generate-cell-model NAME=R0R2C2
make generate-estimator NAME=UKF
```

or call the generators directly:

```bash
tools/generate_cell_model.sh NAME=R0R2C2
tools/generate_estimator.sh NAME=UKF
```
