/**
 * This is not a production server yet!
 * This is only a minimal backend to get started.
 **/

import * as express from 'express';
import * as dotenv from 'dotenv';
import {MongoClient} from 'mongodb';
import * as bcrypt from 'bcrypt';
import * as jwt from 'jsonwebtoken';

dotenv.config();

const web_token_key = process.env.WEB_TOKEN_KEY;
const uri = process.env.BIOSYS_MONGO_URI;
const dbName = 'biosys';
const client = new MongoClient(uri, { useNewUrlParser: true });
const dbPromise = client.connect().then(
  (conn) => {
    return conn.db(dbName)
  }
);

const users_collection = () => {
  return dbPromise.then((db) => {
    return db.collection('users')
  })
}

const ms_ms_experiments_collection = () => {
  return dbPromise.then((db) => {
    return db.collection('ms_ms_experiments');
  })
}

const create_user = (data: any) => {
  return users_collection().then(
    (users) => {
      const {email, password } = data;
      const salt = bcrypt.genSaltSync(5);
      const encrypted_password = bcrypt.hashSync(password,salt);
      return users.insertOne({email,encrypted_password});
    }
  )
}


const app = express();

app.post('/api/users',(req,res) => {
  const {email, password } = req.body;
  users_collection().then(
    (users) => {
      return users.findOne({email});
    }).then(
    (found) => {
      if(found !== null) {
        res.status(403).json({error: 'email is taken'});
      } else {
        create_user({email, password }).then(
          () => {
            res.status(201).json({});
          }
        )
      }
    }
  ).catch((err) => {
     res.status(500).end();
  });
});

app.post('/api/signin',(req,res)=> {
   const {email, password } = req.body;
   dbPromise.then((db) => {
     return db.collection('users')
   }).then(
     (coll) => {
       return coll.findOne({email})
     }
   ).then (
     (found) => {
       if(found !== null) {
        const {_id, encrypted_password} = found;
        if(bcrypt.compareSync(password,encrypted_password) === true) {
          const token = jwt.sign({sub: _id, expiresIn: '1d'},web_token_key);
          res.setHeader("Authorization", `Bearer ${token}`);
          res.status(201).json({});
        } else {
          res.status(401).json({error: 'invalid email or password'});
        }
       } else {
        res.status(401).json({error: 'invalid email or password'});
       }
     }
   ).catch((err) => {
     res.status(500).end();
   });
});

app.use('/api/*',(req,res,next) => {
  const authorization = req.header("Authorization");
  if(authorization) {
    const [_,token] = authorization.split(' ');
    if(token) {
      try {
        const decoded = jwt.verify(token, web_token_key) as object;
        const {_id} = decoded['sub'];
        res.locals.user_id = _id;
        next();
      } catch {
        res.status(401).json({});
      }

    } else {
      res.status(401).json({});
    }
  } else {
    res.status(401).json({});
  }
});

app.get('/api/ms_ms_experiments',(req,res) => {
   const user_id = res.locals.user_id;
   const params: ParamsDictionary = req.params;
   let retmax = req.params['retmax'];//("retmax","10");
   if(retmax === null) {
     retmax = "10";
   }
   ms_ms_experiments_collection().then(
     (experiments) => {
       return experiments.find({user_id}).limit(parseInt(retmax,10)).toArray();
     }
   ).then(
     (experiments) => {
       res.status(200).json({experiments});
     }
   ).catch((err) => {
    res.status(500).end();
  });
})

// app.get('/api', (req, res) => {
//   res.send({ message: 'Welcome to backend!' });
// });

const port = process.env.port || 3000;
const server = app.listen(port, () => {
  console.log(`Listening at http://localhost:${port}/api`);
});
server.on('error', console.error);
