#
# basic tests of FIELDWIDTHS setting of fixed width fields
#
BEGIN {
  FIELDWIDTHS="2 14 10 3"
  OFS="~~"
}
{ 
  print $2,$1,$4,$3; 
  FS=FS
}
