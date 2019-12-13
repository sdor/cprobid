import { Injectable } from '@angular/core';
import { HttpClient, HttpParams } from '@angular/common/http';
import { JwtHelperService } from '@auth0/angular-jwt';


@Injectable({
  providedIn: 'root'
})
export class AccountService {


  constructor(private http: HttpClient, private jwt: JwtHelperService) { }

  get token() {
    return localStorage.getItem("access_token");
  }

  userSignedIn() {
    return this.jwt.isTokenExpired();
    // return this.token !== null && this.token !== undefined && this.token !== '' && this.jwt;
  }
  public signup(email: string, password: string , password_confirmation: string) {
    // let params = new HttpParams();
    // params = params.append("email",email);
    // params = params.append("password",password);
    // params = params.append("password_confirmation",password_confirmation);
    return this.http.post('/api/users',{
      user: {email, password, password_confirmation}
    });
  }
  public signin(email: string, password: string) {
    return this.http.post('/api/users/sign_in',{
     user: {email,password}
    });
    // return this.tokenService.signIn({
    //   login:    email,
    //   password: password
    // })
  }
}
