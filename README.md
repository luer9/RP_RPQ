# Comparative System Analysis
 

| System/Method | Date | Type | Support RPQs | Optimize RPQs | Code | 
| ------------- | ---- | ---- | ------------ | ------------- | ---- |
| Jena          | 2004 |   S  |      1       |       1       |  OS  |
| Virtuoso      | 2006 |   S  |      1       |       1       |  OS  |
| Blazegraph    | 2009 |   S  |      1       |       1       |  OS  |
| TriAD         | 2014 |   D  |      0       |       0       |  OS  |
| AdPart        | 2016 |   D  |      0       |       0       |  OS  |
| OrientDB      | 2013 |   S  |      0       |       0       |  OS  |
| TigerGraph    | 2019 |   D  |      1       |       1       |  OS  |
| DP2RPQ        | 2020 |   D  |      1       |       1       |  NOS  |
| Leon+         | 2021 |   D  |      1       |       1       |  NOS  |
| K-RPQ         | 2016 |   S  |      1       |       1       |  NOS  |
| RTC-Q         | 2022 |   S  |      1       |       1       |  NOS  |

OS: Open-Source; NOS: Not-Open-Source; S: Single; D: Distributed; 1: Yes; 0: No.


Among them, Jena, Virtuoso, and Blazegraph are the more popular open-source DB systems, but Blazegraph cannot guarantee the completeness of RPQs.
OrientDB and TigerGraph are both commercial DBs, which OrientDB is being maintained but still does not support RPQs; TigerGraph provides RPQ-like functionality but does not support declarative RPQs under the standard semantics.
AdPart and TriAD are currently the most advanced distributed RDF engines, but cannot handle RPQs;
Leon+ and DP2RPQ focus more on optimizing RPQs than Kleene closure; K-RPQ and RTC-Q are both approaches to optimize Kleene RPQs, the former using indexing for optimization and the latter proposing graph reduction for optimization, the technical details of which we implemented.

# Query Set



## YAGO2

| index | query                                            | type |
| ----- | ------------------------------------------------ | ---- |
| Y_Q1  | $hasCapital^*$                                   | $KS_{one}$ |
| Y_Q2  | $hasAcademicAdvisor^*$                           | $KS_{one}$ |
| Y_Q3  | $created^*$                                      | $KS_{one}$ |
| Y_Q4  | $hasChild^*$                                     | $KS_{one}$ |
| Y_Q5  | $infulences^{\*}$                                   | $KS_{one}$ |
| Y_Q6  | $dealsWith^{\*}/hasCapital$                         | $KS_{one}$ |
| Y_Q7  | $infulences^{\*}/isMarriedTo^{\*}$                     | $KS_{one}$ |
| Y_Q8  | $isMarriedTo^{\*}/hasChild^{\*}$                       | $KS_{one}$ |
| Y_Q9  | $isKnownFor^{\*}/isMarriedTo^{\*}/hasChild^{\*}$          | $KS_{one}$ |
| Y_Q10 | $infulences^{\*}/isMarriedTo^{\*}/hasChild^{\*}$          | $KS_{one}$ |
| Y_Q11 | $(isConnectedTo/isLocatedIn/owns)^{\*}$             | $KS_{fm}$ |
| Y_Q12 | $(dealsWith/participatedIn/isLocatedIn)^{\*}$       |  $KS_{fm}$ |
| Y_Q13 | $(isLeaderOf/dealsWith/participatedIn)^{\*}$        |  $KS_{fm}$ |
| Y_Q14 | $(influences^{\*}/ isMarriedTo)^{\*}$                  |  $KS_{co}$ |
| Y_Q15 | $((isConnectedTo/isLocatedIn)^{\*}/owns)^{\*}$         |  $KS_{co}$ |
| Y_Q16 | $((dealsWith^{\*}/participatedIn)^{\*}/isLocatedIn)^{\*}$ |  $KS_{co}$ |

## LUBM

 

| index | query                                                        | type |
| ----- | ------------------------------------------------------------ | ---- |
| L_Q1  | $subOrganizationOf^{\*}$                                          | $KS_{one}$ |
| L_Q2  | $worksFor/subOrganizationOf^{\*}$                               | $KS_{one}$ |
| L_Q3  | $headOf/subOrganizationOf^{\*}/name$                            | $KS_{one}$ |
| L_Q4  | $(headOf/subOrganizationOf/memberOf)^{\*}$                      | $KS_{fm}$ |
| L_Q5  | $ResearchGroup/subOrganizationOf^{\*}/University$               | $KS_{one}$ |
| L_Q6  | $FullProfessor/headOf/subOrganizationOf^{\*}/typeUniversity$    | $KS_{one}$ |
| L_Q7  | $ResearchGroup/subOrganizationOf^{\*}/University/ResGroup^{\*}$     | $KS_{one}$ |
| L_Q8  | $(worksFor/subOrganizationOf^{\*})^{\*}$                           | $KS_{co}$ |
| L_Q9  | $((headOf/subOrganizationOf)^{\*}/memberOf)^{\*}$                  | $KS_{co}$ |
| L_Q10 | $(FullProfessor/headOf)^{\*}/(subOrganizationOf^{\*}/typeUniversity)^{\*}$ | $KS_{co}$ |

