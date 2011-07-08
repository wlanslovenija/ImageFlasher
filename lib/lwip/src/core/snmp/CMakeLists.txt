set(snmp_srcs
  asn1_dec.c
  asn1_enc.c
  mib2.c
  mib_structs.c
  msg_in.c
  msg_out.c

)

add_library(lwipsnmp ${snmp_srcs})
target_link_libraries(lwipsnmp ${PROJECT_SOURCE_DIR}/src/lwipcore)
