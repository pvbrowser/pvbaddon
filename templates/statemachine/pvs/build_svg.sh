#!/bin/bash
vi stm2.dot
dot -Tsvg -ostm2.svg stm2.dot
cat stm2.svg

