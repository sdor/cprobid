import { Injectable } from '@angular/core';
import { AngularTokenService } from 'angular-token';

@Injectable({
  providedIn: 'root'
})
export class AccountService {

  constructor(private tokenService: AngularTokenService) { }

  public signup(email: string, password: string , password_confirmation: string) {
    return this.tokenService.registerAccount({
      login:                email,
      password:             password,
      passwordConfirmation: password_confirmation
    })
  }
  public signin(email: string, password: string) {
    return this.tokenService.signIn({
      login:    email,
      password: password
    })
  }
}
