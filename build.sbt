name := "msms_pipeline"

version := "0.1"

scalaVersion := "2.13.1"

val scalaXmlVersion = "1.2.0"

val akkaVersion = "2.5.26"

val alpakkaVersion = "1.1.2"

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


lazy val msms_pipeline = (project in file("."))
 .settings(commonSettings)
 .settings(
     libraryDependencies ++= Seq(
        "org.scala-lang.modules" %% "scala-xml" % scalaXmlVersion,
        "com.lightbend.akka" %% "akka-stream-alpakka-xml" % alpakkaVersion,
        "com.lightbend.akka" %% "akka-stream-alpakka-file" % alpakkaVersion,
     )
 )

scalaVersion in ThisBuild := "2.13.1"
scalacOptions in ThisBuild ++= Seq("-unchecked", "-deprecation", "-feature")

