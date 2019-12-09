package com.biosystechnologies.swissprot

case class Organism(names: List[OrganismName], dbReferences: List[DbReference] = List(), taxons: List[String] = List())
