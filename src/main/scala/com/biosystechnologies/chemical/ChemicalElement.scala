package com.biosystechnologies.chemical

trait ChemicalElement {
  def monoIsotopicMass: Double
  def element: String
  def name: String
  def averageMass: Double
}


case object Hydrogen   extends ChemicalElement {
  val element ="H"
  val name = "Hydrogen"
  val monoIsotopicMass = 1.007825035
  val averageMass = 1.00794
}
case object Deuterium  extends ChemicalElement {
  val element ="D"
  val name = "Deuterium"
  val monoIsotopicMass = 2.014101779
  val averageMass = 2.014101779
}
case object Lithium    extends ChemicalElement {
  val element ="Li"
  val name = "Lithium"
  val monoIsotopicMass = 7.016003
  val averageMass = 6.941
}
case object Boron      extends ChemicalElement {
  val element ="B"
  val name = "Boron"
  val monoIsotopicMass = 11.0093055
  val averageMass = 10.811
}
case object Carbon     extends ChemicalElement {
  val element ="C"
  val name = "Carbon"
  val monoIsotopicMass = 12
  val averageMass = 12.0107
}
case object Carbon13   extends ChemicalElement {
  val element ="C13"
  val name = "Carbon13"
  val monoIsotopicMass = 13.00335483
  val averageMass = 13.00335483
}
case object Nitrogen   extends ChemicalElement {
  val element ="N"
  val name = "Nitrogen"
  val monoIsotopicMass = 14.003074
  val averageMass = 14.0067
}
case object Nitrogen15 extends ChemicalElement {
  val element ="N15"
  val name = "Nitrogen15"
  val monoIsotopicMass = 15.00010897
  val averageMass = 15.00010897
}
case object Oxygen     extends ChemicalElement {
  val element ="O"
  val name = "Oxygen"
  val monoIsotopicMass = 15.99491463
  val averageMass = 15.9994
}
case object Oxygen18   extends ChemicalElement {
  val element ="O18"
  val name = "Oxygen18"
  val monoIsotopicMass = 17.9991603
  val averageMass = 17.9991603
}
case object Fluorine   extends ChemicalElement {
  val element ="F"
  val name = "Fluorine"
  val monoIsotopicMass = 18.99840322
  val averageMass = 18.9984032
}
case object Sodium     extends ChemicalElement {
  val element ="Na"
  val name = "Sodium"
  val monoIsotopicMass = 22.9897677
  val averageMass = 22.98977
}
case object Magnesium  extends ChemicalElement {
  val element ="Mg"
  val name = "Magnesium"
  val monoIsotopicMass = 23.9850423
  val averageMass = 24.305
}
case object Aluminium  extends ChemicalElement {
  val element ="Al"
  val name = "Aluminium"
  val monoIsotopicMass = 26.9815386
  val averageMass = 26.9815386
}
case object Phosphorous extends ChemicalElement {
  val element ="P"
  val name = "Phosphorous"
  val monoIsotopicMass = 30.973762
  val averageMass = 30.973761
}
case object Sulfur     extends ChemicalElement {
  val element ="S"
  val name = "Sulfur"
  val monoIsotopicMass = 31.9720707
  val averageMass = 32.065
}
case object Chlorine   extends ChemicalElement {
  val element ="Cl"
  val name = "Chlorine"
  val monoIsotopicMass = 34.96885272
  val averageMass = 35.453
}
case object Potassium  extends ChemicalElement {
  val element ="K"
  val name = "Potassium"
  val monoIsotopicMass = 38.9637074
  val averageMass = 39.0983
}
case object Calcium    extends ChemicalElement {
  val element ="Ca"
  val name = "Calcium"
  val monoIsotopicMass = 39.9625906
  val averageMass = 40.078
}
case object Chromium   extends ChemicalElement {
  val element ="Cr"
  val name = "Chromium"
  val monoIsotopicMass = 51.9405098
  val averageMass = 51.9961
}
case object Manganese  extends ChemicalElement {
  val element ="Mn"
  val name = "Manganese"
  val monoIsotopicMass = 54.9380471
  val averageMass = 54.938045
}
case object Iron       extends ChemicalElement {
  val element ="Fe"
  val name = "Iron"
  val monoIsotopicMass = 55.9349393
  val averageMass = 55.845
}
case object Nickel     extends ChemicalElement {
  val element ="Ni"
  val name = "Nickel"
  val monoIsotopicMass = 57.9353462
  val averageMass = 58.6934
}
case object Cobalt     extends ChemicalElement {
  val element ="Co"
  val name = "Cobalt"
  val monoIsotopicMass = 58.9331976
  val averageMass = 58.933195
}
case object Copper     extends ChemicalElement {
  val element ="Cu"
  val name = "Copper"
  val monoIsotopicMass = 62.9295989
  val averageMass = 63.546
}
case object Zinc       extends ChemicalElement {
  val element ="Zn"
  val name = "Zinc"
  val monoIsotopicMass = 63.9291448
  val averageMass = 65.409
}
case object Arsenic    extends ChemicalElement {
  val element ="As"
  val name = "Arsenic"
  val monoIsotopicMass = 74.9215942
  val averageMass = 74.9215942
}
case object Bromine    extends ChemicalElement {
  val element ="Br"
  val name = "Bromine"
  val monoIsotopicMass = 78.9183361
  val averageMass =  79.904
}
case object Selenium   extends ChemicalElement {
  val element ="Se"
  val name = "Selenium"
  val monoIsotopicMass = 79.9165196
  val averageMass = 78.96
}
case object Molybdenum extends ChemicalElement {
  val element ="Mo"
  val name = "Molybdenum"
  val monoIsotopicMass =  97.9054073
  val averageMass = 95.94
}
case object Ruthenium  extends ChemicalElement {
  val element ="Ru"
  val name = "Ruthenium"
  val monoIsotopicMass = 101.9043485
  val averageMass = 101.07
}
case object Palladium  extends ChemicalElement {
  val element ="Pd"
  val name = "Palladium"
  val monoIsotopicMass = 105.903478
  val averageMass = 106.42
}
case object Silver     extends ChemicalElement {
  val element ="Ag"
  val name = "Silver"
  val monoIsotopicMass = 106.905092
  val averageMass = 107.8682
}
case object Cadmium    extends ChemicalElement {
  val element ="Cd"
  val name = "Cadmium"
  val monoIsotopicMass = 113.903357
  val averageMass = 112.411
}
case object Iodine     extends ChemicalElement {
  val element ="I"
  val name = "Iodine"
  val monoIsotopicMass = 126.904473
  val averageMass = 126.90447
}
case object Platinum   extends ChemicalElement {
  val element ="Pt"
  val name = "Platinum"
  val monoIsotopicMass = 194.964766
  val averageMass = 195.084
}
case object Gold       extends ChemicalElement {
  val element ="Au"
  val name = "Gold"
  val monoIsotopicMass = 196.966543
  val averageMass = 196.96655
}
case object Mercury    extends ChemicalElement {
  val element ="Hg"
  val name = "Mercury"
  val monoIsotopicMass = 201.970617
  val averageMass = 200.59
}

