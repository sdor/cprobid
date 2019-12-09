name := "msms_pipeline"

version := "0.1"

scalaVersion := "2.13.1"

val scalaXmlVersion = "1.2.0"

val akkaVersion = "2.5.26"

//val alpakkaVersion = "1.1.2"
val alpakkaVersion = "2.0.0-M1"

val akkaHttpVersion = "10.1.10"

val scalaTestVersion = "3.0.8"

val commonSettings = Seq(
  libraryDependencies ++= Seq(
    "com.typesafe" % "config" % "1.4.0",
    "io.github.cdimascio" % "java-dotenv" % "5.1.3",
    "org.scalactic" %% "scalactic" % scalaTestVersion,
    "org.scalatest" %% "scalatest" % scalaTestVersion % Test
  )
)

val akkaSettings = Seq(
  libraryDependencies ++= Seq(
    "com.typesafe.akka" %% "akka-actor" % akkaVersion,
    "com.typesafe.akka" %% "akka-slf4j" % akkaVersion,
    "com.typesafe.akka" %% "akka-testkit" % akkaVersion % Test,
    "com.typesafe.akka" %% "akka-stream" % akkaVersion,
    "com.typesafe.akka" %% "akka-stream-testkit" % akkaVersion % Test
  )
)

val akkaTypedSettings = Seq(
  libraryDependencies ++= Seq(
    "com.typesafe.akka" %% "akka-actor-typed" % akkaVersion,
    "com.typesafe.akka" %% "akka-actor-testkit-typed" % akkaVersion % Test,
    "com.typesafe.akka" %% "akka-stream-typed" % akkaVersion,
  )
)


lazy val api = (project in file("api"))
  .settings(commonSettings)
  .settings(akkaSettings)

lazy val `peptides-store` = (project in file("peptides-store"))

lazy val msms_pipeline = (project in file("."))
 .settings(commonSettings)
 .settings(akkaSettings)
 .settings(
     libraryDependencies ++= Seq(
       "org.scala-lang.modules" %% "scala-xml" % scalaXmlVersion,
       "com.lightbend.akka" %% "akka-stream-alpakka-xml" % alpakkaVersion,
       "com.lightbend.akka" %% "akka-stream-alpakka-file" % alpakkaVersion,
       "org.mongodb.scala" %% "mongo-scala-driver" % "2.7.0",
//       "org.reactivemongo" %% "reactivemongo" % "0.19.1",
       // https://mvnrepository.com/artifact/org.reactivemongo/reactivemongo-bson-macros
//       "org.reactivemongo" %% "reactivemongo-bson-macros" % "0.19.1",
//       "org.reactivemongo" %% "reactivemongo-akkastream" % "0.19.1",
       "com.lightbend.akka" %% "akka-stream-alpakka-mongodb" % alpakkaVersion
     )
 )

scalaVersion in ThisBuild := "2.13.1"
scalacOptions in ThisBuild ++= Seq("-unchecked", "-deprecation", "-feature")

