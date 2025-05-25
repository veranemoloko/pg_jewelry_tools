#include "postgres.h"

#include "fmgr.h"

#define GOLD 0
#define SILVER 1
#define PLATINUM 2

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(calculate_metal_weight);

static double get_density(int metal_enum, int purity) {
  switch (metal_enum) {
  case GOLD:
    switch (purity) {
    case 375:
      return 11.54;
    case 585:
      return 13.24;
    case 750:
      return 15.45;
    case 999:
      return 19.32;
    default:
      ereport(ERROR, (errmsg("Unknown gold purity: %d", purity)));
    }
    break;
  case SILVER:
    switch (purity) {
    case 800:
      return 10.15;
    case 875:
      return 10.30;
    case 925:
      return 10.40;
    case 960:
      return 10.45;
    default:
      ereport(ERROR, (errmsg("Unknown silver purity: %d", purity)));
    }
    break;
  case PLATINUM:
    switch (purity) {
    case 850:
      return 20.50;
    case 900:
      return 20.70;
    case 950:
      return 21.45;
    default:
      ereport(ERROR, (errmsg("Unknown platinum purity: %d", purity)));
    }
    break;
  default:
    ereport(ERROR, (errmsg("Unknown metal type enum: %d", metal_enum)));
  }
  return 0.0;
}

Datum calculate_metal_weight(PG_FUNCTION_ARGS) {
  int metal_enum = PG_GETARG_INT32(0);
  int purity = PG_GETARG_INT32(1);
  double volume = PG_GETARG_FLOAT8(2);

  double density = get_density(metal_enum, purity);
  double weight = volume * density / 1000.0;

  PG_RETURN_FLOAT8(weight);
}
