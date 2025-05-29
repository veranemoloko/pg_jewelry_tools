#include "postgres.h"

#include "fmgr.h"
#include "math.h"
#include "utils/builtins.h"
#include "utils/elog.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(calculate_metal_weight_gr);
PG_FUNCTION_INFO_V1(calculate_gemstone_gr_to_carat);
PG_FUNCTION_INFO_V1(calculate_gemstone_carat_to_gr);

static double round_3d(double num) { return round(num * 1000.0) / 1000.0; }

Datum calculate_gemstone_gr_to_carat(PG_FUNCTION_ARGS) {
  if (PG_ARGISNULL(0))
    PG_RETURN_NULL();

  double weight_gr = PG_GETARG_FLOAT8(0);
  if (weight_gr <= 0)
    ereport(ERROR, (errmsg("Error: weight <= 0")));

  double carat = weight_gr / 0.2;
  PG_RETURN_FLOAT8(round_3d(carat));
}

Datum calculate_gemstone_carat_to_gr(PG_FUNCTION_ARGS) {
  if (PG_ARGISNULL(0))
    PG_RETURN_NULL();

  double carat = PG_GETARG_FLOAT8(0);
  if (carat <= 0)
    ereport(ERROR, (errmsg("Error: carat <= 0")));

  double weight_gr = carat * 0.2;
  PG_RETURN_FLOAT8(round_3d(weight_gr));
}

Datum calculate_metal_weight_gr(PG_FUNCTION_ARGS) {
  if (PG_ARGISNULL(0) || PG_ARGISNULL(1) || PG_ARGISNULL(2))
    PG_RETURN_NULL();

  text *metal_text = PG_GETARG_TEXT_PP(0);
  int purity = PG_GETARG_INT32(1);
  double volume_mm3 = PG_GETARG_FLOAT8(2);

  if (purity <= 0 || purity > 1000)
    ereport(ERROR, (errmsg("Error: purity <= 0 or > 1000")));
  if (volume_mm3 <= 0)
    ereport(ERROR, (errmsg("Error: volume <= 0")));

  char *metal_str = text_to_cstring(metal_text);
  double density = 0.0;

  if (strcmp(metal_str, "gold") == 0) {
    switch (purity) {
    case 375:
      density = 11.54;
      break;
    case 585:
      density = 13.24;
      break;
    case 750:
      density = 15.45;
      break;
    case 999:
      density = 19.32;
      break;
    default:
      ereport(ERROR, (errmsg("Unknown gold purity: %d", purity)));
    }
  } else if (strcmp(metal_str, "silver") == 0) {
    switch (purity) {
    case 800:
      density = 10.15;
      break;
    case 875:
      density = 10.30;
      break;
    case 925:
      density = 10.40;
      break;
    case 960:
      density = 10.45;
      break;
    default:
      ereport(ERROR, (errmsg("Unknown silver purity: %d", purity)));
    }
  } else if (strcmp(metal_str, "platinum") == 0) {
    switch (purity) {
    case 850:
      density = 20.50;
      break;
    case 900:
      density = 20.70;
      break;
    case 950:
      density = 21.45;
      break;
    default:
      ereport(ERROR, (errmsg("Unknown platinum purity: %d", purity)));
    }
  } else {
    ereport(ERROR, (errmsg("Unknown metal type: %s", metal_str)));
  }

  double weight_gr = volume_mm3 * density / 1000.0;

  PG_RETURN_FLOAT8(round_3d(weight_gr));
}
